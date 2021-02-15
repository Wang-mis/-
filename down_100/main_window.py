import random
import sys
from line import *
from player import *
from score_board import *
from start_button import *
from items import *


# TODO：
# 1.平台功能实现 OK
# 2.道具
# 3.计分 OK
# 4.平台上升速度随时间增加 OK
# 5.人物贴图翻转 OK
# 6.改善外观 OK
# 7.BGM OK
# 8.开始界面 OK
# 9.难度调整
# 10.微调

class Game:
    def __init__(self):
        # 创建设置类
        self.settings = Settings()
        # 初始化pygame
        pygame.init()
        # 设置窗口大小
        self.screen_size = (self.screen_width, self.screen_height) = self.settings.screen_size
        # 获取窗口对象
        self.screen = pygame.display.set_mode(self.screen_size)
        self.screen_rect = self.screen.get_rect()
        # 设置标题
        pygame.display.set_caption(self.settings.screen_caption)
        # 设置背景
        self.start_background = self.settings.start_background
        self.start_bg_image = pygame.image.load(self.start_background)
        self.start_bg_image = pygame.transform.scale(self.start_bg_image, self.screen_size)
        self.background = self.settings.game_background
        self.bg_image = pygame.image.load(self.background)
        self.bg_image = pygame.transform.scale(self.bg_image, self.screen_size)
        # 创建开始按钮
        self.start_button = StartButton(self)
        # 创建平台组
        self.lines = Group()
        # 创建 Player
        self.player = Player(self)
        self.player_move_left = False
        self.player_move_right = False
        self.player_sink = True
        self.player_rise = False
        # 创建道具
        self.items = Group()
        # 分数
        self.score = 0
        # 计分板
        self.score_board = ScoreBoard(self)
        # 游戏难度
        self.difficulty = self.settings.line_default_rise_speed
        # 延时时间
        self.delay_time = self.settings.game_default_delay_time
        # 游戏暂停标志
        self.pause = False
        # 游戏暂停界面
        self.pause_image = pygame.image.load("image/pause.png").convert_alpha()
        self.pause_image = pygame.transform.scale(self.pause_image, self.screen_size)
        # 游戏结束标志
        self.game_over = False
        # 游戏结束界面
        self.lose_image = pygame.image.load("image/lose.png").convert_alpha()
        self.lose_image = pygame.transform.scale(self.lose_image, self.screen_size)

    def startMenu(self):
        # 游戏BGM
        pygame.mixer.music.load("music/bgm.mp3")
        pygame.mixer.music.play(-1)
        # 游戏启动标志
        buttonBeClicked = False
        gameStart = False
        # 事件循环
        while True:
            for event in pygame.event.get():
                # 退出
                if event.type == pygame.QUIT:
                    sys.exit()
                elif event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        sys.exit()
                # 鼠标点击事件
                elif event.type == pygame.MOUSEBUTTONDOWN:
                    mouse_pos = pygame.mouse.get_pos()
                    if self.start_button.ifBeClicked(mouse_pos):
                        self.start_button.beClicked()
                        buttonBeClicked = True
                elif event.type == pygame.MOUSEBUTTONUP:
                    if buttonBeClicked:
                        self.start_button.back()
                        gameStart = True
            # 绘制背景
            self.screen.fill(self.settings.bg_color)
            self.screen.blit(self.start_bg_image, self.screen_rect)
            # 绘制按钮
            self.start_button.blitMe()
            # 延时
            pygame.time.delay(self.delay_time)
            # 刷新
            pygame.display.flip()
            # 开始游戏
            if gameStart:
                pygame.time.delay(150)
                self.start()

    def start(self):
        # 初始化
        # 创建初始平台
        self.createInitialLines()
        # 事件循环
        while True:
            for event in pygame.event.get():
                # 退出
                if event.type == pygame.QUIT:
                    sys.exit()
                elif event.type == pygame.KEYDOWN:
                    self.keyDown(event)
                elif event.type == pygame.KEYUP:
                    self.keyUp(event)
            # 绘制背景
            self.screen.blit(self.bg_image, self.screen_rect)
            # 创建平台及道具
            self.createLines()
            # 更新平台位置
            self.updateLines()
            # 判断主角是否应该下落
            self.playerSink()
            # 更新主角位置
            self.updatePlayer()
            # 绘制平台
            self.lines.draw(self.screen)
            # 绘制道具
            self.items.update()
            self.items.draw(self.screen)
            # 更新道具位置
            self.updateItems()
            # 放置计分板
            self.score_board.blitMe()
            # 判断游戏是否结束
            self.gameOver()
            # 绘制暂停界面
            if self.pause:
                self.screen.blit(self.pause_image, self.screen_rect)
            # 绘制结束界面
            if self.game_over:
                self.screen.blit(self.lose_image, self.screen_rect)
                self.score_board.lose()
            # 刷新
            pygame.display.flip()
            # 延时
            pygame.time.delay(self.delay_time)

    # 创建初始平台
    def createInitialLines(self):
        x = self.screen_width // 2 - self.settings.line_width // 2
        y = self.screen_height // 2
        line = SimpleLine(self)
        line.setPosition(x, y)
        self.lines.add(line)
        for y in range(self.screen_height // 2 + self.settings.lines_distance,
                       self.screen_height, self.settings.lines_distance):
            x = random.randint(0, self.screen_width - self.settings.line_width)
            line = SimpleLine(self)
            line.setPosition(x, y)
            self.lines.add(line)

    # 增加游戏难度
    def increaseDifficulty(self):
        self.difficulty += 1
        for line in self.lines:
            line.setSpeed(self.difficulty)

    # 判断主角是否应该下落
    def playerSink(self):
        if self.pause or self.game_over:
            self.player_sink = False
            self.player_rise = False
            self.player.line = None
            return
        self.player_sink = True
        self.player_rise = False
        self.player.line = None
        for line in self.lines:
            if line.rect.top - (self.player.sink_speed + line.speed) \
                    <= self.player.rect.bottom \
                    <= line.rect.top + (self.player.sink_speed + line.speed) \
                    and line.rect.left <= self.player.rect.right \
                    and self.player.rect.left <= line.rect.right:
                self.player_sink = False
                self.player_rise = True
                self.player.line = line
                if line.type == 2:
                    self.game_over = True
                elif line.type == 3:
                    line.disappear()
                return

    # 判断游戏是否结束
    def gameOver(self):
        if self.player.rect.y >= self.screen_height or self.player.rect.top <= 0 or self.game_over:
            self.game_over = True

    # 键盘按下事件响应
    def keyDown(self, event):
        # 按下ESC键退出
        if event.key == pygame.K_ESCAPE:
            sys.exit()
        if self.pause:
            if event.key == pygame.K_SPACE:
                self.pause = False
            return
        # 按下A键或左方向键控制小人左移
        elif event.key == pygame.K_a or event.key == pygame.K_LEFT:
            self.player_move_left = True
        # 按下D键或右方向键控制小人右移
        elif event.key == pygame.K_d or event.key == pygame.K_RIGHT:
            self.player_move_right = True
        elif event.key == pygame.K_SPACE:
            if not self.game_over:
                self.player_move_right = False
                self.player_move_left = False
                self.player.move_state = 0
                self.pause = True
            else:
                sys.exit()

    # 键盘松开事件响应
    def keyUp(self, event):
        if self.pause:
            return
        if event.key == pygame.K_a or event.key == pygame.K_LEFT:
            self.player_move_left = False
            self.player.move_state = 0
        elif event.key == pygame.K_d or event.key == pygame.K_RIGHT:
            self.player_move_right = False
            self.player.move_state = 0

    # 更新主角位置
    def updatePlayer(self):
        if self.pause or self.game_over:
            self.player.blitMe()
            return
        # 左移
        if self.player_move_left:
            self.player.moveLeft()
        # 右移
        if self.player_move_right:
            self.player.moveRight()
        # 下落
        if self.player_sink:
            self.player.sink()
        # 上升
        if self.player_rise:
            self.player.rise()
        # 站立不动
        if self.player.move_state == 0:
            self.player.stand()
        # 重绘小人图形
        self.player.blitMe()

    # 更新平台位置，并将超出屏幕限制的平台删除
    def updateLines(self):
        if self.pause or self.game_over:
            return
        self.lines.update()
        for line in self.lines:
            # 将超出屏幕的平台删除，节省内存空间
            if line.rect.bottom <= 0:
                line.kill()  # sprite类的方法，能够将自身从所有精灵组（Group）中删除

    # 创建新平台，每创建一个新平台，则加一分，平台上可能会出现道具
    def createLines(self):
        if self.pause or self.game_over:
            return
        willCreate = True
        for line in self.lines:
            if line.rect.bottom > self.screen_height - self.settings.lines_distance:
                willCreate = False
        if willCreate:
            line = None
            # 创建随机类型的平台
            kind = random.choice(self.settings.lines_type_seed)
            if kind == 1:
                line = SimpleLine(self)
            elif kind == 2:
                line = PoisonLine(self)
            elif kind == 3:
                line = SnowLine(self)
            line_x = random.randint(0, self.screen_width - self.settings.line_width)
            line.setPosition(line_x, self.screen_height)
            self.lines.add(line)
            # 创建道具
            if line.type != 2 and random.randint(1, 5) == 1:
                self.createItems(line)
            # 记分
            self.score += 1
            if self.score % 20 == 0:
                self.increaseDifficulty()

    def createItems(self, line):
        item = None
        kind = random.choice(self.settings.items_type_seed)
        if kind == 1:
            item = SpeedUpItem(self, line)
        line.item = item
        self.items.add(item)

    def updateItems(self):
        for item in self.items:
            if item.rect.bottom <= 0 or item.line is None:
                item.kill()
        self.items.update()


if __name__ == '__main__':
    game = Game()
    game.startMenu()
