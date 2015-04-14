# -*- mode: ruby -*-
# vi: set ft=ruby :

proxyHTTP = 'http://10.140.55.133:8080/'
proxyHTTPS = 'http://10.140.55.133:8443/'

VAGRANTFILE_API_VERSION = "2"
BOX = "hashicorp/precise32"
IP = "192.168.50.50"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  #if Vagrant.has_plugin?("vagrant-proxyconf")
    #config.proxy.http     = proxy
    #config.proxy.https    = proxy
    #config.proxy.no_proxy = 'localhost,127.0.0.1'
  #end
  
  # Assign this VM a unique hostname
  config.vm.host_name = "serverC.local"
  
  config.vm.box = BOX
  
  config.vm.network "public_network"
  
  #config.vm.network "private_network", ip: IP
  #config.vm.network "forwarded_port", guest: 80, host: 80
  #config.vm.network "forwarded_port", guest: 22, host: 2200
  
  #config.vm.provision :puppet, :module_path => "modules" do |puppet|
    #puppet.manifests_path = "manifests"
    #puppet.manifest_file  = "default.pp"
  #end
end