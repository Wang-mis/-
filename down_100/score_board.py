import pygame
from settings import Settings


class ScoreBoard:
    def __init__(self, game):
        self.settings = Settings()
        self.game = game
        self.score = game.score
        self.color = self.settings.score_board_color
        self.screen = game.screen
        self.position = self.settings.score_board_position
        self.size = self.settings.score_board_size
        self.font = pygame.font.Font(None, self.size)
        self.image = None
        self.rect = None

    def lose(self):
        self.rect.center = self.game.screen_rect.center
        self.screen.blit(self.image, self.rect)

    def blitMe(self):
        self.score = self.game.score
        self.image = self.font.render(f"Score:{self.score}", True, self.color)
        self.rect = self.image.get_rect()
        self.screen.blit(self.image, self.rect)
