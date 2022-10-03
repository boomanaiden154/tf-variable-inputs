saved-model:
	python3 saved-model.py

test-saved-model:
	clang++ test-saved-model.cpp -I /usr/local/lib/python3.10/dist-packages/tensorflow/include -ltensorflow -L /tmp/tensorflow/lib -o test-saved-model 

clean:
	rm -rf ./adder-saved-model
	rm -rf ./test-saved-model
