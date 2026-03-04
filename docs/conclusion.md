# Conclusion

Ce tutoriel ne vise qu'à offrir un aperçu de ce que l'on peut faire avec raylib, et en général avec des bibliothèques graphiques. Il n'est donc, de loin, pas exhaustif. Quand on ne sait pas comment faire quelque chose, il ne faut pas hésiter à chercher dans la documentation ou parmi les exemples. Il ne faut ainsi pas hésiter à regarder les divers liens proposés au fur et à mesure de ce tutoriel.

---

# Annexe : Pourquoi apprendre à utiliser une bibliothèque graphique ?

Dans le cadre des études de mathématiques ou de physique, il peut paraitre superflu d'apprendre à utiliser une bibliothèque graphique, car on ne vise pas à développer des applications ni des jeux vidéos. Néanmoins, les compétences acquises dans ce domaine peuvent facilement être transposées pour d'autres cas d'usages. Par exemple, pour visualiser des données, on retrouvera des patterns assez similaires à ceux présentés :

```python
import matplotlib.pyplot as plt
import numpy as np

t = np.linspace(-10, 10, 100)
sig = 1 / (1 + np.exp(-t))

fig, ax = plt.subplots()
ax.axhline(y=0, color="black", linestyle="--")
ax.axhline(y=0.5, color="black", linestyle=":")
ax.axhline(y=1.0, color="black", linestyle="--")
ax.axvline(color="grey")
ax.axline((0, 0.5), slope=0.25, color="black", linestyle=(0, (5, 5)))
ax.plot(t, sig, linewidth=2, label=r"$\sigma(t) = \frac{1}{1 + e^{-t}}$")
ax.set(xlim=(-10, 10), xlabel="t")
ax.legend(fontsize=14)
plt.show()
```

afin de produire un graphique comme suit via le module [`matplotlib`](https://matplotlib.org/) de Python :

![mpl.png](mpl.png)

Il existe aussi des outils d'animation pour de la vulgarisation qui se basent sur de la programmation telle que [manim](https://docs.manim.community/en/stable/), créé par Grant Sanderson, le créateur de la chaîne YouTube [3Blue1Brown](https://www.youtube.com/@3blue1brown).

```python
from manim import *

class FollowingGraphCamera(MovingCameraScene):
    def construct(self):
        self.camera.frame.save_state()

        # create the axes and the curve
        ax = Axes(x_range=[-1, 10], y_range=[-1, 10])
        graph = ax.plot(lambda x: np.sin(x), color=BLUE, x_range=[0, 3 * PI])

        # create dots based on the graph
        moving_dot = Dot(ax.i2gp(graph.t_min, graph), color=ORANGE)
        dot_1 = Dot(ax.i2gp(graph.t_min, graph))
        dot_2 = Dot(ax.i2gp(graph.t_max, graph))

        self.add(ax, graph, dot_1, dot_2, moving_dot)
        self.play(self.camera.frame.animate.scale(0.5).move_to(moving_dot))

        def update_curve(mob):
            mob.move_to(moving_dot.get_center())

        self.camera.frame.add_updater(update_curve)
        self.play(MoveAlongPath(moving_dot, graph, rate_func=linear))
        self.camera.frame.remove_updater(update_curve)

        self.play(Restore(self.camera.frame))
```

produisant une animation comme suit :

![manim.gif](manim.gif)

On trouve des similarités entre chacun de ces outils, avec par exemple quels concepts permettent quelles configurations, comment structurer un code quand on a une idée graphique en tête, etc.

Nous avons choisi raylib car elle fournit déjà un bon nombre de fonctionnalités et permet d'arriver assez vite/simplement à des résultats satisfaisants. De plus, si dans des cours passés certain(e)s ont pu se familiariser avec d'autres bibliothèques graphiques (p.ex. [`pygame`](https://www.pygame.org)) des similarités seront évidentes, p.ex. en comparant ce code issu de la documentation de `pygame` avec ceux que l'on a fait ic avec raylib :

```python
# Example file showing a circle moving on screen
import pygame

# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True
dt = 0

player_pos = pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2)

while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")

    pygame.draw.circle(screen, "red", player_pos, 40)

    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        player_pos.y -= 300 * dt
    if keys[pygame.K_s]:
        player_pos.y += 300 * dt
    if keys[pygame.K_a]:
        player_pos.x -= 300 * dt
    if keys[pygame.K_d]:
        player_pos.x += 300 * dt

    # flip() the display to put your work on screen
    pygame.display.flip()

    # limits FPS to 60
    # dt is delta time in seconds since last frame, used for framerate-
    # independent physics.
    dt = clock.tick(60) / 1000

pygame.quit()
```

On y remarque en effet la préparation de la fenêtre, la boucle principale qui gère les événements, et la fin de la boucle qui ferme la fenêtre, avec des noms de méthodes qui ne sont pas très éloignés.
