tensorflowArchives = /tflite/tensorflow/lib/libtensorflow-lite.a /tflite/tensorflow/lib/libfarmhash.a /tflite/tensorflow/lib/libfft2d_fftsg.a /tflite/tensorflow/lib/libfft2d_fftsg2d.a
flatbufferArchives = /tflite/flatbuffers/lib/libflatbuffers.a
ruyArchives = /tflite/ruy/lib/libruy_context_get_ctx.a /tflite/ruy/lib/libruy_context.a /tflite/ruy/lib/libruy_frontend.a /tflite/ruy/lib/libruy_kernel_arm.a /tflite/ruy/lib/libruy_kernel_avx.a /tflite/ruy/lib/libruy_kernel_avx2_fma.a /tflite/ruy/lib/libruy_kernel_avx512.a /tflite/ruy/lib/libruy_apply_multiplier.a /tflite/ruy/lib/libruy_pack_arm.a /tflite/ruy/lib/libruy_pack_avx.a /tflite/ruy/lib/libruy_pack_avx2_fma.a /tflite/ruy/lib/libruy_pack_avx512.a /tflite/ruy/lib/libruy_prepare_packed_matrices.a /tflite/ruy/lib/libruy_trmul.a /tflite/ruy/lib/libruy_ctx.a /tflite/ruy/lib/libruy_allocator.a /tflite/ruy/lib/libruy_prepacked_cache.a /tflite/ruy/lib/libruy_system_aligned_alloc.a /tflite/ruy/lib/libruy_have_built_path_for_avx.a /tflite/ruy/lib/libruy_have_built_path_for_avx2_fma.a /tflite/ruy/lib/libruy_have_built_path_for_avx512.a /tflite/ruy/lib/libruy_thread_pool.a /tflite/ruy/lib/libruy_blocking_counter.a /tflite/ruy/lib/libruy_wait.a /tflite/ruy/lib/libruy_denormal.a /tflite/ruy/lib/libruy_block_map.a /tflite/ruy/lib/libruy_tune.a /tflite/ruy/lib/libruy_cpuinfo.a /tflite/ruy/lib/libruy_profiler_instrumentation.a
cpuinfoArchives = /tflite/cpuinfo/lib/libcpuinfo.a /tflite/cpuinfo/lib/libclog.a
allArchives = $(tensorflowArchives) $(flatbufferArchives) $(ruyArchives) $(cpuinfoArchives)

saved-model:
	python3 saved-model.py

tflite-model-from-saved-model: saved-model
	tflite_convert --saved_model_dir=./adder-saved-model --output_file=adder-tflite.tflite

test-saved-model:
	clang++ test-saved-model.cpp -I /usr/local/lib/python3.10/dist-packages/tensorflow/include -ltensorflow -L /tmp/tensorflow/lib -O3 -o test-saved-model

test-tflite:
	clang++ test-tflite.cpp $(allArchives) -I /tflite/tensorflow/include -I /tflite/flatbuffers/include -I /tflite/ruy/include -I /tflite/cpuinfo/include -O3 -o test-tflite

clean:
	rm -rf ./adder-saved-model
	rm -rf ./test-saved-model
	rm -rf ./test-tflite
	rm -rf ./*.tflite
