<template>
  <div class="container">
    <div class="align-items-right">
      <FormLogin/>
    </div>
  </div>
</template>

<script>
import FormLogin from '../components/FormLogin.vue'
export default {
  name: 'login',
  layout: 'default',
  component: {FormLogin}
};
</script>

<style lang="scss" scoped>
</style>