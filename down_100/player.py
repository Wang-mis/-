import pygame
from settings import Settings


class Player:
    def __init__(self, game):
        self.settings = Settings()
        self.size = (self.width, self.height) = self.settings.player_size
        self.image = pygame.image.load("image/player/p1_stand.png").convert_alpha()
        self.image = pygame.transform.scale(self.image, self.size)
        self.image_direction = self.settings.player_default_direction
        self.move_state = 0
        self.rect = self.image.get_rect()
        self.setPosition(*self.settings.player_default_position)
        self.game = game
        self.screen = game.screen
        self.line = None
        self.lines = game.lines
        self.move_speed = self.settings.player_move_speed
        self.sink_speed = self.settings.player_sink_speed
        self.image_stand = None
        self.images = [self.image for _ in range(12)]
        self.initImage()

    def initImage(self):
        self.image_stand = pygame.image.load("image/player/p1_stand.png").convert_alpha()
        self.image_stand = pygame.transform.scale(self.image, self.size)
        self.images[0] = self.image_stand
        for i in range(1, 12):
            self.images[i] = \
                pygame.transform.scale(pygame.image.load(f"image/player/p1_walk{i}.png").convert_alpha(),
                                       self.size)

    def stand(self):
        self.image = self.images[0]
        if self.image_direction == "left":
            self.image = pygame.transform.flip(self.image, True, False)

    def setPosition(self, x, y):
        self.rect.left = x
        self.rect.bottom = y

    def moveLeft(self):
        if self.image_direction == "right":
            self.move_state = 0
            self.image_direction = "left"
        if self.move_state == 11:
            self.move_state = 0
        self.move_state += 1
        self.image = self.images[self.move_state]
        self.image = pygame.transform.flip(self.image, True, False)
        if self.rect.x <= 0:
            return
        for line in self.lines:
            if line.rect.right - self.move_speed \
                    <= self.rect.left \
                    <= line.rect.right + self.move_speed \
                    and (self.rect.top <= line.rect.top <= self.rect.bottom
                         or self.rect.top <= line.rect.bottom <= self.rect.bottom):
                return
        self.rect.x -= self.move_speed

    def moveRight(self):
        if self.image_direction == "left":
            self.move_state = 0
            self.image_direction = "right"
        if self.move_state == 11:
            self.move_state = 0
        self.move_state += 1
        self.image = self.images[self.move_state]
        if self.rect.right >= self.settings.screen_width:
            return
        for line in self.lines:
            if line.rect.left - self.move_speed \
                    <= self.rect.right \
                    <= line.rect.left + self.move_speed \
                    and (self.rect.top <= line.rect.top <= self.rect.bottom
                         or self.rect.top <= line.rect.bottom <= self.rect.bottom):
                return
        self.rect.x += self.move_speed

    def sink(self):
        if self.rect.y >= self.settings.screen_height:
            return
        self.rect.y += self.sink_speed

    def rise(self):
        self.rect.bottom = self.line.rect.top

    def blitMe(self):
        self.screen.blit(self.image, self.rect)
