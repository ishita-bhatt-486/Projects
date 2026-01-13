# Physics Engine

from turtle import distance
import pygame
import random
import math

# Parameters
WIDTH, HEIGHT = 800, 600
FPS = 60
GRAVITY = 0.5
FRICTION = 0.99 
WALL_ELASTICITY = 0.8
COLLISION_DAMPING = 0.9

WHITE = (255, 255, 255)
BLACK = (20, 20, 20)
RED = (200, 50, 50)
BLUE = (50, 50, 200)
GREEN = (50, 200, 50)
GRAY = (100, 100, 100)
YELLOW = (255, 255, 0)

initialPositions = [-5, -4, -3, 3, 4, 5]

# Pygame Setup
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Physics Engine")
clock = pygame.time.Clock()

#Balls
class Ball:
    def __init__(self, x, y, radius, color):
        self.x = x
        self.y = y
        self.radius = radius
        self.color = color
        self.dx = random.choice(initialPositions)
        self.dy = random.choice(initialPositions)
        self.mass = radius * radius
        self.isdragging = False

    def apply_physics(self):
        
        if self.isdragging:
            return

        #general
        self.dy += GRAVITY

        self.dx *= FRICTION
        self.dy *= FRICTION

        self.x += self.dx
        self.y += self.dy

        # wall collisions
        if self.x + self.radius > WIDTH:
            self.x = WIDTH - self.radius
            self.dx *= -WALL_ELASTICITY
        elif self.x - self.radius < 0:
            self.x = self.radius
            self.dx *= -WALL_ELASTICITY
            
        if self.y + self.radius > HEIGHT:
            self.y = HEIGHT - self.radius
            self.dy *= -WALL_ELASTICITY

            if abs(self.dy) < GRAVITY * 2:
                self.dy = 0

        elif self.y - self.radius < 0:
            self.y = self.radius
            self.dy *= -WALL_ELASTICITY

    def draw(self, surface):
        pygame.draw.circle(surface, self.color, (int(self.x), int(self.y)), self.radius)

    def isClickInsideBall(self, position):
        mx, my = position
        distance = math.sqrt((mx - self.x)**2 + (my - self.y)**2)
        return distance <= self.radius

class Button:
    def __init__(self, x, y, width, height, text):
        self.rect = pygame.Rect(x, y, width, height)
        self.text = text
        self.font = pygame.font.SysFont('Arial', 24)
    
    def draw(self, surface):
        pygame.draw.rect(surface, GRAY, self.rect)
        pygame.draw.rect(surface, WHITE, self.rect, 2)

        text_surface = self.font.render(self.text, True, WHITE)
        text_rectangle = text_surface.get_rect(center=self.rect.center)

        surface.blit(text_surface, text_rectangle)

    def is_clicked(self, pos):
        return self.rect.collidepoint(pos)

# collisions
def resolve_collisions(balls):
    for i in range(len(balls)):
        for j in range(i + 1, len(balls)):
            b1 = balls[i]
            b2 = balls[j]

            dx = b2.x - b1.x
            dy = b2.y - b1.y
            distance = math.sqrt((dx)**2 + (dy)**2)

            if distance < b1.radius + b2.radius:
                overlap = (b1.radius + b2.radius - distance)

                # direction of collision
                nx = dx / distance
                ny = dy / distance

                # new positions
                b1.x -= nx * (overlap / 2)
                b1.y -= ny * (overlap / 2)
                b2.x += nx * (overlap / 2)
                b2.y += ny * (overlap / 2)

                # new velocities
                tx = -ny
                ty = nx

                dpTan1 = b1.dx * tx + b1.dy * ty
                dpTan2 = b2.dx * tx + b2.dy * ty

                dpNorm1 = b1.dx * nx + b1.dy * ny
                dpNorm2 = b2.dx * nx + b2.dy * ny

                m1 = (dpNorm1 * (b1.mass - b2.mass) + 2 * b2.mass * dpNorm2) / (b1.mass + b2.mass)
                m2 = (dpNorm2 * (b2.mass - b1.mass) + 2 * b1.mass * dpNorm1) / (b1.mass + b2.mass)

                m1 *= COLLISION_DAMPING
                m2 *= COLLISION_DAMPING

                b1.dx = tx * dpTan1 + nx * m1
                b1.dy = ty * dpTan1 + ny * m1
                b2.dx = tx * dpTan2 + nx * m2
                b2.dy = ty * dpTan2 + ny * m2

def main():
    running = True
    balls = [Ball(400, 200, 30, BLUE)]
    add_button = Button(10, 10, 150, 50, "Add Ball")
    
    draggedBall = None

    while running:

        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                running = False
            
            elif event.type == pygame.MOUSEBUTTONDOWN:
                
                if event.button == 1:
                    if add_button.is_clicked(event.pos):
                        r = random.randint(15, 35)
                        x = random.randint(r + 50, WIDTH - r - 50)
                        y = random.randint(r + 50, 300)
                        color = (random.randint(50,255), random.randint(50,255), random.randint(50,255))
                        balls.append(Ball(x, y, r, color))
                    
                    else:
                        for ball in reversed(balls):
                            if ball.isClickInsideBall(event.pos):
                                ball.isdragging = True
                                draggedBall = ball
                                break
            
            elif event.type == pygame.MOUSEBUTTONUP:
                if event.button == 1:
                    if draggedBall:
                        draggedBall.isdragging = False
                        draggedBall = None

            elif event.type == pygame.MOUSEMOTION:
                if draggedBall:
                    draggedBall.x, draggedBall.y = event.pos
                    
                    draggedBall.dx = event.rel[0]
                    draggedBall.dy = event.rel[1]

        for ball in balls:
            ball.apply_physics()
        
        resolve_collisions(balls)

        screen.fill(BLACK)
        for ball in balls:
            ball.draw(screen) 
        add_button.draw(screen)

        font = pygame.font.SysFont("Courier", 16)
        info = font.render(f"Balls: {len(balls)} (Click to Add, Drag to Throw)", True, WHITE)
        screen.blit(info, (180, 25))

        pygame.display.flip()
        clock.tick(FPS)

    pygame.quit()

if __name__ == "__main__":
    main()