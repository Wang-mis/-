import pygame
from pygame import Rect
from pygame.sprite import *
from settings import Settings


class Line(Sprite):
    def __init__(self, game):
        super(Line, self).__init__()
        self.settings = Settings()
        self.color = self.settings.line_color
        self.size = (self.width, self.height) = self.settings.line_size
        self.rect = Rect(*self.settings.line_default_position, *self.size)
        self.speed = game.difficulty
        self.screen = game.screen
        self.item = None
        self.type = 0

    def kill(self) -> None:
        if self.item:
            self.item.kill()
        Sprite.kill(self)

    def increaseSpeed(self, s=1):
        self.speed += s

    def setSpeed(self, speed):
        self.speed = speed

    def update(self):
        self.rect.y -= self.speed

    def setPosition(self, x, y):
        self.rect.x = x
        self.rect.y = y

    def blitMe(self):
        pygame.draw.rect(self.screen, self.color, self.rect)


class SimpleLine(Line):
    def __init__(self, game):
        super(SimpleLine, self).__init__(game)
        self.type = 1
        self.color = self.settings.simple_line_color
        self.image = pygame.image.load("image/simple_line.png").convert_alpha()
        self.image = pygame.transform.scale(self.image, self.size)


class PoisonLine(Line):
    def __init__(self, game):
        super(PoisonLine, self).__init__(game)
        self.type = 2
        self.color = self.settings.poison_line_color
        self.image = pygame.image.load("image/stone.png").convert_alpha()
        self.image = pygame.transform.scale(self.image, self.size)


class SnowLine(Line):
    def __init__(self, game):
        super(SnowLine, self).__init__(game)
        self.type = 3
        self.color = self.settings.snow_line_color
        self.image = pygame.image.load("image/snow.png").convert_alpha()
        self.image = pygame.transform.scale(self.image, self.size)
        self.willDisappear = 0

    def disappear(self):
        self.willDisappear += 1
        if self.willDisappear == 50:
            self.kill()
