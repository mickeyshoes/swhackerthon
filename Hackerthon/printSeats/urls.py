from django.urls import path, include
from . import views

app_name='print_seat'

urlpatterns = [
    path('', views.main, name='main'),
]