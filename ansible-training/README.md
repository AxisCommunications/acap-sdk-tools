# Training on an AWS EC2 Instance using Ansible

## Requirements:

- Ansible 5 with AWS collection installed ([community.aws](https://docs.ansible.com/ansible/latest/collections/community/aws/index.html))

### Recommendation:

Instead of installing Ansible directly on the computer, you can create a virtual environment:
	
```
sudo apt install python3-virtualenv
virtualenv ansible-venv
source ansible-venv/bin/activate
pip3 install ansible
ansible-galaxy collection install community.aws
pip3 install -r $HOME/.ansible/collections/ansible_collections/amazon/aws/requirements.txt
```

## Structure of this example

```bash
ansible-training
├── inventory
│   ├── group_vars
│   │   └── vars.yaml
│   └── inventory_aws_ec2.yaml
├── playbooks
│   └── deploy.yaml
├── ansible.cfg
└── README.md
```

- **inventory/group_vars/vars.yaml** - Defines the variables used by the playbook.
- **inventory/inventory_aws_ec2.yaml** - Defines the dynamic inventory used by the playbook.
- **playbooks/deploy.yaml** - The main playbook that deploys the instance and trains.
- **ansible.cfg** - A configuration file for Ansible.


## Quicksteps

The main file in this repository is the Ansible playbook. Ansible is an automation framework that, in this case, connects to Amazon Web Services (AWS). In this example, we are automating the training process for the [tensorflow-to-larod-artpec8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/tensorflow-to-larod-artpec8) example. 

If this is the first time you are using AWS or Ansible:

1. Create an IAM group with Administrator Access policies.
2. Create an IAM user associated with the IAM group and download the credentials. It is important that you choose "Access key" for the user type, that way we will have access through the CLI.
3. Once created, you will have the credentials. Export them in your terminal with the names ```AWS_ACCESS_KEY``` and ```AWS_SECRET_KEY```.
4. Create a key-pair in AWS, download its .pem file and copy it to your working directory. The configuration provided is based on you naming this key pair following ```$USER-key-pair```. Each EC2 instance needs to be attached to a key-pair and, with only that, you will be able to access it. 
5. Give permission to Ansible to use this key by: ```chmod 400 $USER-key-pair.pem```.

After that, you will be able to run the playbook:

1. Configure the variables that are in "inventory/group_vars/vars.yaml". The one that you need to change is ```EXAMPLE_DIRECTORY```; the others are not mandatory.

2. Configure your user in the dynamic inventory. This is important, because we only want to run the training in the instance we are going to create ourselves.

3. Run the playbook:

```
ansible-playbook playbooks/deploy.yaml --private-key $USER-key-pair.pem
```

## Playbook explanation

There are different things that are necessary to complete the whole pipeline.

1. Getting my public IP.
2. Creating security group and allowing SSH access: 
A security group defines how to access an EC2 Instance. In this case, only SSH from your IP is allowed to access it.
3. Creating the EC2 instance: 
The instance is created. Different configurations can be made, like the type of image or instance. To be able to create it, we use the key-pair. We also attach it to the security group we created in the last step.
4. Adding instance to inventory: 
Once we have the IP address (and DNS name) to connect to the instance, we can add it to the invetory. This will allow us to register this IP and use it in the next steps.
5. Writing the new EC2 instance host key to known hosts:
Sometimes, there are problems with checking the host. For Ansible to be truly automatised, we add the instance to known hosts so that there is no connection problems.
6. Train prep: 
We copy the necessary data to the instance.
7. Building environment in instance: 
We build an environment with the characteristics we want. Most importantly, the specific Tensorflow version.
8. Training: 
The training and model conversion is done.
9. Collecting model: 
We copy the model from the instance to local.
10. Terminating AWS instance: 
Once we have the model, we can terminate the instance and prevent forgetting about it.
11. Removing from known_hosts:
To finish, we reverse what was done in step 5.


### Network configuration
The EC2 instance is created in what Amazon calls a Virtual Private Cloud (VPC). In this notebook, we are using the default VPC that AWS provides. There are four steps that one has to do to build their own VPC:

1. Create VPC (main Ansible module: [ec2_vpc_net](https://docs.ansible.com/ansible/latest/collections/amazon/aws/ec2_vpc_net_module.html))
2. Create Internet Gate to define access from/to the EC2 instance (main Ansible module: [ec2_vpc_igw]())
3. Create subnet to allocate IP for instance (main Ansible module: [ec2_vpc_subnet]())
4. Give public access to the subnet (main Ansible module: [ec2_vpc_route_table]())
