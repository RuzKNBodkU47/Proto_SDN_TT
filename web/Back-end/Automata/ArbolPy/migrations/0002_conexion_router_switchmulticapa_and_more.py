# Generated by Django 4.0.2 on 2022-02-23 22:17

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('ArbolPy', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Conexion',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('idConnComp', models.SlugField(max_length=15)),
                ('tipo_cable', models.CharField(max_length=30)),
                ('extremoIni', models.CharField(max_length=15)),
                ('extremoFin', models.CharField(max_length=15)),
            ],
        ),
        migrations.CreateModel(
            name='Router',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('idRoutComp', models.SlugField(max_length=15)),
                ('dirIP', models.GenericIPAddressField()),
                ('num_puertos', models.DecimalField(decimal_places=0, max_digits=3)),
                ('velocidad_trans', models.DecimalField(decimal_places=0, max_digits=3)),
                ('unidad_trans', models.SlugField(max_length=5)),
                ('color', models.SlugField(max_length=10)),
                ('dirMAC', models.CharField(max_length=17)),
                ('status', models.CharField(max_length=20)),
                ('protocolo', models.CharField(max_length=8)),
                ('tipo_conexion', models.CharField(max_length=30)),
            ],
        ),
        migrations.CreateModel(
            name='SwitchMulticapa',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('idSwMultComp', models.SlugField(max_length=15)),
                ('dirMac', models.CharField(max_length=17)),
                ('num_Puertos', models.DecimalField(decimal_places=0, max_digits=3)),
                ('velocidad_trans', models.DecimalField(decimal_places=0, max_digits=3)),
                ('color', models.SlugField(max_length=10)),
                ('tipo_conexion', models.CharField(max_length=30)),
                ('status', models.CharField(max_length=20)),
            ],
        ),
        migrations.RenameModel(
            old_name='PruebaComponente',
            new_name='Componente',
        ),
        migrations.CreateModel(
            name='Switch',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('idSWComp', models.SlugField(max_length=15)),
                ('dirMac', models.CharField(max_length=17)),
                ('num_Puertos', models.DecimalField(decimal_places=0, max_digits=3)),
                ('velocidad_trans', models.DecimalField(decimal_places=0, max_digits=3)),
                ('color', models.SlugField(max_length=10)),
                ('tipo_conexion', models.CharField(max_length=30)),
                ('status', models.CharField(max_length=20)),
                ('tipo_comp', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='ArbolPy.componente')),
            ],
        ),
    ]
