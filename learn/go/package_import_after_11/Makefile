img_ver=v0.0.1
img_name=test_pack

build:
	docker build -t $(img_name):$(img_ver) .
	docker image ls | grep $(img_name)

export:
	docker save -o ../$(img_name)$(img_ver).tar $(img_name):$(img_ver)

debug:
	docker run -it --rm --name "test_instance" --entrypoint "/go/bin/adapter" $(img_name):$(img_ver)
