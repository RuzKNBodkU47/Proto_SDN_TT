from django.contrib import admin

# Registro de los modelos creados por el equipo en el archivo models.py en la carpeta ArbolPy.
from ArbolPy.models import Componente, Elemento, SubRedIMG

#Indicar a django que administre el modelo por medio del sitio de administrador
admin.site.register(Componente)
admin.site.register(Elemento)
admin.site.register(SubRedIMG)