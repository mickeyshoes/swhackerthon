from django.urls import path, include
from . import views

app_name='print_seat'

urlpatterns = [
    path('', views.main, name='main'),
    path('introduce/', views.introduce, name="introduce"),
    path('policy/', views.policy, name="policy"),
    path('service/', views.service, name="service"),
    path('get_seat/', views.getSeatInfo, name="get_seat"),
    path('seat/', views.seat, name="seat"),
]