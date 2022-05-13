*Copyright (C) 2022, Axis Communications AB, Lund, Sweden. All Rights Reserved.*

# Training on an AWS EC2 Instance using Ansible

Some applications need a trained model to infer a result. We provide examples like [object detection](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/object-detection) and [pose estimation](https://github.com/AxisCommunications/acap-computer-vision-sdk-examples/tree/master/pose-estimator-with-flask). In one example in particular, [tensorflow-to-larod-artpec8](https://github.com/AxisCommunications/acap-native-sdk-examples/tree/master/tensorflow-to-larod-artpec8), we show you how to train a model for object detection and how to use it in the camera since training requires a specific environment, not only in software but also in hardware. We provide the tool to train your model in Amazon Web Services (AWS) so that you don't have to build the setup on your own computer. Additionally, we use Ansible, which is an automation framework that in this case automates the deployment of an EC2 instance and all the training.

## Requirements

- Ansible 5 with AWS collection installed ([community.aws](https://docs.ansible.com/ansible/latest/collections/community/aws/index.html))
- AWS account

### Building the environment

Instead of installing Ansible directly on the computer, you can create a virtual environment or run a small Ubuntu Docker container. The Dockerfile only needs a few lines:

```dockerfile
FROM arm64v8/ubuntu:latest
RUN apt-get update && apt-get -y install python3-pip
RUN pip3 install ansible
RUN ansible-galaxy collection install community.aws
RUN pip3 install -r $HOME/.ansible/collections/ansible_collections/amazon/aws/requirements.txt
CMD ["/bin/bash"]
```

1. Pulls the Ubuntu image
2. Installs PIP, a Python package manager
3. Installs Ansible
4. Installs the AWS collection
5. Installs the requirements for the AWS collection
6. Opens the command line

## Structure of this tool

```sh
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

1. Create an IAM user group with *AdministratorAccess* policies.
2. Create an IAM user associated with the IAM user group and download the credentials. It's important that you choose "Access key" for the user type. That way you'll have access through the CLI.
3. Once created, you'll have the credentials. Export them in your terminal with the names `AWS_ACCESS_KEY` and `AWS_SECRET_KEY`.
4. Create a key-pair in AWS, download its .pem file, and copy it to your working directory. The configuration provided requires using syntax `$USER-key-pair` when naming this key-pair. Each EC2 instance must be attached to a key-pair, which is your only way of accessing it.
5. Give permission to Ansible to use this key by: `chmod 400 $USER-key-pair.pem`.

Now you can run the playbook:

1. Configure the variables that are located in "inventory/group_vars/vars.yaml". The one you need to change is `EXAMPLE_DIRECTORY`. The rest are optional.
2. Configure your user in the dynamic inventory. This is important, because we only want to run the training in the instance we're going to create ourselves.
3. Run the playbook:

```sh
ansible-playbook playbooks/deploy.yaml --private-key $USER-key-pair.pem
```

In the diagram below, you can see an explanation of all the security steps needed to connect to an EC2 instance.

![Security diagram](data/security_diagram.svg)

## Playbook explanation

All the steps below are defined in the Ansible playbook which is the main file in this repository. To complete the whole pipeline you must:

1. Get your public IP.
2. Create a security group[^1] and allow SSH access.
3. Create the EC2 instance[^2].
4. Add the instance to the inventory[^3].
5. Write the new EC2 instance host key to known_hosts[^4].
6. Copy the necessary data to the instance to prepare for training.
7. Build the environment in the instance[^5].
8. Train (training and model conversion is done).
9. Copy the model from the EC2 instance to your local machine to collect the model.
10. Terminate AWS instance[^6].
11. Remove from known_hosts (reverse step 5)
[^1]: A security group defines how to access an EC2 Instance. In this case, only SSH from your IP is allowed to access it.
[^2]: The instance is created. Different configurations can be made, like the type of image or instance. To be able to create it, the key-pair is used. Also, it's attached to the security group created in the last step.
[^3]: Once you have the IP address (and DNS name) to connect to the instance, you can add it to the invetory. This allows you to register this IP and use it in the next steps.
[^4]: Sometimes, there are problems connecting the host. For Ansible to be truly automated, you can add the instance to known_hosts so that there are no connection problems.
[^5]: Build an environment with the characteristics you want. Most importantly for this example, the specific Tensorflow version.
[^6]: Once you have the model, you can terminate the instance and prevent forgetting about it.

### Network configuration

The EC2 instance is created in what Amazon calls a Virtual Private Cloud (VPC). In this notebook, we're using the default VPC that AWS provides. To build your own VPC:

1. Create VPC (main Ansible module: [ec2_vpc_net](https://docs.ansible.com/ansible/latest/collections/amazon/aws/ec2_vpc_net_module.html))
2. Create Internet Gate to define access to or from the EC2 instance (main Ansible module: [ec2_vpc_igw](https://docs.ansible.com/ansible/latest/collections/community/aws/ec2_vpc_igw_module.html))
3. Create subnet to allocate IP for instance (main Ansible module: [ec2_vpc_subnet](https://docs.ansible.com/ansible/latest/collections/amazon/aws/ec2_vpc_subnet_module.html))
4. Give public access to the subnet (main Ansible module: [ec2_vpc_route_table](https://docs.ansible.com/ansible/latest/collections/amazon/aws/ec2_vpc_route_table_module.html))

## License

[Apache 2.0](../LICENSE)

## References

- [https://docs.ansible.com/ansible](https://docs.ansible.com/ansible)
- [https://docs.aws.amazon.com](https://docs.aws.amazon.com)
