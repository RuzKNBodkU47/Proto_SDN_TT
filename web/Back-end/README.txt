Orden de los comandos en los que se deben correr las migraciones

php artisan migrate -> Para correr todas las migraciones
php artisan migrate:fresh  -> Para refrescar todas las migraciones

php artisan migrate:fresh --pathc:\Users\juoha\Desktop\TT-Back\database\migrations\2022_01_07_155658_create_administradores_table.php -> La primera que se tira si no contiene llaves foráneas
php artisan migrate:fresh --path=2022_01_07_155658_create_administradores_table.php -> La segunda migración sin llaves foráneas
php artisan migrate:fresh --path=c:\Users\juoha\Desktop\TT-Back\database\migrations\2022_01_07_155658_create_administradores_table.php -> Tercera migración sin llaves foráneas
php artisan migrate:fresh --path=app/database/migrations/2022_01_07_155658_create_administradores_table.php -> Cuarta migración con llaves foráneas
php artisan migrate:refresh --path=app/database/migrations/2022_01_07_155658_create_administradores_table.php
php artisan migrate:fresh --path=database/migrations/2022_01_07_155658_create_administradores_table.php      

php artisan migrate:refresh --path=database/migrations/2022_01_07_155658_create_administradores_table.php   
php artisan migrate:refresh --path=database/migrations/2022_01_07_181405_create_cat_tareas_administradores_table.php   
php artisan migrate:refresh --path=database\migrations\2022_01_07_180923_create_administrador_servicios_logs_table.php 
php artisan migrate:refresh --path=database\migrations\2022_01_07_180154_create_administrador_tareas_logs_table.php    
php artisan migrate:refresh --path=database/migrations/2022_01_07_172324_create_cat_servicios_administradores_table.php


Orden de los comandos
php artisan migrate:refresh --path=database\migrations\2022_01_07_170608_create_status_admins_table.php 
php artisan migrate:refresh --path=database\migrations\2022_01_07_170630_create_tipo_admins_table.php   
php artisan migrate:refresh --path=database\migrations\2022_01_07_171316_create_status_logs_table.php 
php artisan migrate:refresh --path=database\migrations\2022_01_07_175538_create_cat_servicios_table.php  
php artisan migrate:refresh --path=database\migrations\2022_01_07_175941_create_cat_tareas_table.php 
php artisan migrate:refresh --path=database/migrations/2022_01_07_155658_create_administradores_table.php 
php artisan migrate:refresh --path=database\migrations\2022_01_07_180154_create_administrador_tareas_logs_table.php  
php artisan migrate:refresh --path=database/migrations/2022_01_07_172324_create_cat_servicios_administradores_table.php
php artisan migrate:refresh --path=database\migrations\2022_01_07_181405_create_cat_tareas_administradores_table.php   
php artisan migrate:refresh --path=database\migrations\2022_01_07_180923_create_administrador_servicios_logs_table.php 
