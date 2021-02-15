from settings import Settings
import pygame


class StartButton:
    def __init__(self, game):
        self.settings = Settings()
        self.screen = game.screen
        self.screen_rect = game.screen_rect
        self.size = (self.width, self.height) = self.settings.button_size
        self.position = self.settings.button_position
        self.image = pygame.image.load("image/start_button.png").convert_alpha()
        self.image = pygame.transform.scale(self.image, self.size)
        self.rect = self.image.get_rect()
        self.setPosition(*self.position)

    def beClicked(self):
        self.rect.y += 5

    def back(self):
        self.setPosition(*self.position)

    def ifBeClicked(self, mouse_pos):
        return self.rect.left <= mouse_pos[0] <= self.rect.right \
               and self.rect.top <= mouse_pos[1] <= self.rect.bottom

    def setPosition(self, x, y):
        self.rect.x = x
        self.rect.y = y

    def blitMe(self):
        self.screen.blit(self.image, self.rect)
