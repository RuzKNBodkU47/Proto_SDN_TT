# Generated by Django 2.2.12 on 2022-03-26 20:30

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('ArbolPy', '0007_redscan_idescaneo'),
    ]

    operations = [
        migrations.AlterField(
            model_name='redscan',
            name='idEscaneo',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='ArbolPy.RedScan'),
        ),
    ]
