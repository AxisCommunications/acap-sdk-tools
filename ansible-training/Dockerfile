FROM arm64v8/ubuntu:latest

ARG AWS_ACCESS_KEY
ARG AWS_SECRET_KEY
ARG USER
ENV AWS_ACCESS_KEY=$AWS_ACCESS_KEY
ENV AWS_SECRET_KEY=$AWS_SECRET_KEY
ENV USER=$USER

RUN apt-get update && apt-get -y install python3-pip ssh
RUN pip3 install ansible
RUN ansible-galaxy collection install community.aws
RUN pip3 install -r $HOME/.ansible/collections/ansible_collections/amazon/aws/requirements.txt

RUN mkdir $HOME/.ssh && chmod 400 $HOME/.ssh && touch $HOME/.ssh/known_hosts
WORKDIR /app
COPY . .

CMD ["ansible-playbook playbooks/deploy.yaml --private-key $USER-key-pair.pem"]

