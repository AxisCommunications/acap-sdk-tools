FROM arm64v8/ubuntu:latest

RUN apt-get update && apt-get -y install python3-pip
RUN pip3 install ansible
RUN ansible-galaxy collection install community.aws
RUN pip3 install -r $HOME/.ansible/collections/ansible_collections/amazon/aws/requirements.txt

CMD ["/bin/bash"]
