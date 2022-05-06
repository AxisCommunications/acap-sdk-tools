*Copyright (C) 2022, Axis Communications AB, Lund, Sweden. All Rights Reserved.*

# Training on an AWS EC2 Instance using Ansible

Ansible is an automation framework that, in this case, connects to Amazon Web Services (AWS). In this tool, we are automating the training process for the [tensorflow-to-larod-artpec8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/tensorflow-to-larod-artpec8) example.

## Requirements

- Ansible 5 with AWS collection installed ([community.aws](https://docs.ansible.com/ansible/latest/collections/community/aws/index.html))
- AWS account

### Recommendation

Instead of installing Ansible directly on the computer, you can create a virtual environment:

```sh
sudo apt install python3-virtualenv
virtualenv ansible-venv
source ansible-venv/bin/activate
pip3 install ansible
ansible-galaxy collection install community.aws
pip3 install -r $HOME/.ansible/collections/ansible_collections/amazon/aws/requirements.txt
```

## Structure of this tool

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

If this is the first time you are using AWS or Ansible:

1. Create an IAM group with Administrator Access policies.
2. Create an IAM user associated with the IAM group and download the credentials. It is important that you choose "Access key" for the user type, that way we will have access through the CLI.
3. Once created, you will have the credentials. Export them in your terminal with the names ```AWS_ACCESS_KEY``` and ```AWS_SECRET_KEY```.
4. Create a key-pair in AWS, download its .pem file and copy it to your working directory. The configuration provided is based on you naming this key-pair following ```$USER-key-pair```. Each EC2 instance needs to be attached to a key-pair and, with only that, you will be able to access it.
5. Give permission to Ansible to use this key by: ```chmod 400 $USER-key-pair.pem```.

After that, you will be able to run the playbook:

1. Configure the variables that are in "inventory/group_vars/vars.yaml". The one that you need to change is ```EXAMPLE_DIRECTORY```; the others are not mandatory.

2. Configure your user in the dynamic inventory. This is important, because we only want to run the training in the instance we are going to create ourselves.

3. Run the playbook:

```sh
ansible-playbook playbooks/deploy.yaml --private-key $USER-key-pair.pem
```

In the following diagram, you can see an explanation of all the security steps needed to connect to an EC2 instance.

![Security diagram](data/security_diagram.svg)

## Playbook explanation

There are different steps that are necessary to complete the whole pipeline. The main file in this repository is the Ansible playbook, where all these steps are defined.

1. Getting your public IP.
2. Creating security group and allowing SSH access:
A security group defines how to access an EC2 Instance. In this case, only SSH from your IP is allowed to access it.
3. Creating the EC2 instance:
The instance is created. Different configurations can be made, like the type of image or instance. To be able to create it, the key-pair is used. Also, it is attached to the security group created in the last step.
4. Adding instance to inventory:
Once you have the IP address (and DNS name) to connect to the instance, you can add it to the invetory. This will allow you to register this IP and use it in the next steps.
5. Writing the new EC2 instance host key to known_hosts:
Sometimes, there are problems with connecting the host. For Ansible to be truly automatised, the instance can be added to known_hosts so that there are no connection problems.
6. Train prep:
Copy the necessary data to the instance.
7. Building environment in instance:
Build an environment with the characteristics you want. Most importantly for this example, the specific Tensorflow version.
8. Training:
The training and model conversion is done.
9. Collecting model:
Copy the model from the EC2 instance to your local machine.
10. Terminating AWS instance:
Once you have the model, you can terminate the instance and prevent forgetting about it.
11. Removing from known_hosts:
To finish, what was done in step 5 is reversed.

### Network configuration

The EC2 instance is created in what Amazon calls a Virtual Private Cloud (VPC). In this notebook, we are using the default VPC that AWS provides. There are four steps that one has to do to build their own VPC:

1. Create VPC (main Ansible module: [ec2_vpc_net](https://docs.ansible.com/ansible/latest/collections/amazon/aws/ec2_vpc_net_module.html))
2. Create Internet Gate to define access from/to the EC2 instance (main Ansible module: [ec2_vpc_igw](https://docs.ansible.com/ansible/latest/collections/community/aws/ec2_vpc_igw_module.html))
3. Create subnet to allocate IP for instance (main Ansible module: [ec2_vpc_subnet](https://docs.ansible.com/ansible/latest/collections/amazon/aws/ec2_vpc_subnet_module.html))
4. Give public access to the subnet (main Ansible module: [ec2_vpc_route_table](https://docs.ansible.com/ansible/latest/collections/amazon/aws/ec2_vpc_route_table_module.html))

# License

[Apache 2.0](../LICENSE)

# References

- [https://docs.ansible.com/ansible](https://docs.ansible.com/ansible)
- [https://docs.aws.amazon.com](https://docs.aws.amazon.com)
