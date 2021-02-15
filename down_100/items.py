from settings import Settings
import pygame
from pygame.sprite import *


class Item(Sprite):
    def __init__(self, game, line, *groups: AbstractGroup):
        super().__init__(*groups)
        self.settings = Settings()
        self.image = None
        self.rect = None
        self.size = (self.width, self.height) = self.settings.item_size
        self.screen = game.screen
        self.line = line

    def blitMe(self):
        self.screen.blit(self.image, self.rect)

    def update(self, *args, **kwargs) -> None:
        self.rect.bottom = self.line.rect.top


class SpeedUpItem(Item):
    def __init__(self, game, line):
        super().__init__(game, line)
        self.image = pygame.image.load("image/speed_up.png").convert_alpha()
        self.image = pygame.transform.scale(self.image, self.size)
        self.rect = self.image.get_rect()
        self.rect.centerx = self.line.rect.centerx
