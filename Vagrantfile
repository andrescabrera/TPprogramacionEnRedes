# -*- mode: ruby -*-
# vi: set ft=ruby :

proxyHTTP = 'http://10.140.55.133:8080/'
proxyHTTPS = 'http://10.140.55.133:8443/'

VAGRANTFILE_API_VERSION = "2"
BOX = "hashicorp/precise32"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|

  config.vm.provider "virtualbox" do |v|
	v.memory = 2048
    v.cpus = 4
  end

  if Vagrant.has_plugin?("vagrant-proxyconf")
    config.proxy.http     = proxy
    config.proxy.https    = proxy
    config.proxy.no_proxy = 'localhost,127.0.0.1'
  end
  
  # Assign this VM a unique hostname
  config.vm.host_name = "stash.cfa.local"
  
  config.vm.box = BOX
  #config.vm.network "public_network"
  config.vm.network "forwarded_port", guest: 7990, host: 7990
  config.vm.network "forwarded_port", guest: 8443, host: 8443
  config.vm.network "forwarded_port", guest: 22, host: 2200
  config.vm.provision :puppet, :module_path => "modules" do |puppet|
    puppet.manifests_path = "manifests"
    puppet.manifest_file  = "default.pp"
  end
end