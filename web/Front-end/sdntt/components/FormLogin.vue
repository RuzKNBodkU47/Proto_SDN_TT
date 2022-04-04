<template>
    <div class="container">
        <div align="center">
            <b-card title="Inicio de sesion" style="background-color: #6b123c" class="border mt-5"> 
                <b-form @submit.stop.prevent="h">
                    <b-form-group id="input-group-1" label="Nombre usuario" label-for="input-1">
                        <b-form-input v-model="usuario.username" id="input-1" type="text" required placeholder="Ingesar nombre de usuario"></b-form-input>
                    </b-form-group>
                    <b-form-group id="input-group-2" label="Contraseña" label-for="input-2">
                        <b-form-input v-model="usuario.password" id="input-2" type="password" required placeholder="Ingresa tu contraseña"></b-form-input>
                    </b-form-group>
                    <b-button type="submit">Iniciar sesión</b-button>
                </b-form>
            </b-card>
        </div>
    </div>
</template>

<script>
export default {
    name:'FormLogin',
    data(){
        return{
            usuario:{
                username:null,
                password:null
            }
        }
    },
    computed:{
        
    },
    methods:{
        async loginuser(){
            let msg = await this.$store.dispatch("admin/setinfo", this.usuario);
        }
    }
}
</script>