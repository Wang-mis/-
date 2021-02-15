class Settings:
    def __init__(self):

        # Game
        self.bg_color = (200, 200, 200)
        self.screen_size \
            = (self.screen_width, self.screen_height) \
            = (550, 850)
        self.screen_caption = "100"
        self.game_default_delay_time = 8
        self.game_background = "image/bg_1.jpg"
        self.start_background = "image/start_bg.jpg"
        # StartButton
        self.button_size \
            = (self.button_width, self.button_height) \
            = (250, 250)
        self.button_position \
            = (self.screen_width / 2 - self.button_width / 2,
               self.screen_height * 4 / 5 - self.button_height / 2)
        # Line
        self.line_size \
            = (self.line_width, self.line_height) \
            = (150, 30)
        self.line_color = (0, 255, 0)
        self.simple_line_color = self.line_color
        self.poison_line_color = (255, 0, 0)
        self.snow_line_color = (0, 0, 255)
        self.line_default_position = \
            (0, self.screen_height)
        self.line_default_rise_speed = 1
        self.line_rise_speed_growth_rate = 1
        self.lines_distance = 200
        self.lines_total_type = 3
        self.lines_type_seed = (1, 1, 1, 2, 3, 3)
        # Player
        self.player_default_direction = "right"
        self.player_size \
            = (self.player_width, self.player_height) \
            = (40, 50)
        self.player_default_position \
            = (self.screen_width / 2, self.screen_height / 2)
        self.player_move_speed = 2
        self.player_sink_speed = 3
        # ScoreBoard
        self.score_board_size = 40
        self.score_board_position = (0, 0)
        self.score_board_color = (0, 0, 0)
        # Items
        self.item_size \
            = (self.item_width, self.item_height) \
            = (70, 80)
        self.items_total_type = 1
        self.items_type_seed = (1,)
