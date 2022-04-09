<template>
  <div>
      <Header/>
      <div class="container">
          <table class="table table-hover">
              <thead>
                  <tr>
                      <th scope="col">Nombre Administrator</th>
                      <th scope="col">Nombre Usuario</th>
                      <th scope="col">Apellido Paterno</th>
                      <th scope="col">Apellido Materno</th>
                      <th scope="col">Id Status Admin</th>
                      <th scope="col">Id Tipo Admin</th>
                  </tr>
              </thead>
              <tbody>
                  <tr v-for="admin in Listaadmins" :key="admin.Id_Administradores">
                      <td >{{admin.Nombre_Admin}}</td>
                      <td >{{admin.Nombre_Usuario}}</td>
                      <td >{{admin.Apellido_P_Admin}}</td>
                      <td >{{admin.Apellido_M_Admin}}</td>
                      <td >{{admin.Id_Status_Admin}}</td>
                      <td >{{admin.Id_Tipo_Admin}}</td>
                  </tr>
              </tbody>    
          </table>
      </div>
  </div>
</template>
<script>
import Header from '../components/Header.vue';
import axios from 'axios';
import apiTT from '../repositories/Repository'
export default {
    name:'home',
    data(){
        return {
            Listaadmins:null,
        }
    },
    components:{
        Header
    },
    mounted:function(){
        let admin = 'http://127.0.0.1:8000/api/muestra';
        axios.get(admin).then(data => {
            console.log(data);
            this.Listaadmins = data.data;
        }) 
    }
}
</script>