#!/bin/bash
Fedora=fedora
Ubuntu=Ubuntu
OP_SYSTEM_F= cat /etc/*release | grep '^ID'|grep fedora
OP_SYSTEM_U= cat /etc/*release | grep '^NAME'|grep ubuntu
echo "==> Configurando Servidor FTP"
date


function fedorainstallftp {
    echo "<== Fedora system ==>"
    #sudo dnf upgrade
    #sudo dnf -y install vsftpd 
    echo "==> Activando servicio vsftpd "
    #sudo systemctl enable --now vsftpd
    echo "==> Habilitando servicio ftp en firewall "
    #firewall-cmd --add-service=ftp 
    #firewall-cmd --runtime-to-permanent
}

function fedoraunistallftp{
echo "==> Desinstalando vsftpd"
if [[ rpm -q vsftpd ]] ; then
    #sudo dnf remove vsftpd
fi
echo "==> Servidor FTP desinstalado"
}


function ubuntuinstallftp {
    echo "<== Ubuntu system ==>"
    #sudo apt upgrade
    #sudo apt -y install vsftpd 
    #sudo systemctl restart vsftpd 
}

function ubuntuunistallftp{

}


if [[ "$OP_SYSTEM_F" = "ID=fedora" ]] ; then
    echo "<== Fedora system ==>"
    fedora

fi

if [[ "$OP_SYSTEM_U" = "ubuntu" ]] ; then
    echo "<== Ubuntu system ==>"
    ubuntu
fi