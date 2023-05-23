# Code 

Contient l'integralité du code de notre Projet.

## Objectif 
Pour rappel, nous avons pour objectif de créer un robot qui map un labyrinthe. Pour cela, il sera equipé de plusieurs capteurs. Par exemple, une centrale inertielle, une caméra ainsi que des encodeurs rotatifs. 

## Installation / Déploiment

Pour compiler et deployer notre projet, voici quelques instructions :

### La compilation
> Nécessite arm-none-eabi-gcc
```
git clone https://github.com/Suicide-Quad/Quad.git
cd Quad
make
``` 
### Le déploimemt
```
st-flash write build/Suicide-Quad.bin 0x8000000
```

## Autres Repo 
- [PCB](https://github.com/atelier-lyon/Robot_Main_Board)
- [MAP](https://github.com/Suicide-Quad/Map)
- [Communication](https://github.com/Suicide-Quad/Communication/Cam)
- [Server](https://github.com/Suicide-Quad/Communication/Server)

## Contribution

- [MrVym](https://github.com/MrVyM)
- [FlorianRUIZ](https://github.com/FlorianRUIZ)
- [Tcheka](https://github.com/Tchekda)
- [AzerX2](https://github.com/AzerX2)
