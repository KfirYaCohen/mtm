COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG

matamikya: matamikya.o matamikya_product.o matamikya_order.o matamikya_print.o matamikya_main.o matamikya_tests.o libas.a libmtm.a
	gcc matamikya.o matamikya_product.o matamikya_order.o matamikya_print.o matamikya_main.o matamikya_tests.o libas.a libmtm.a -o matamikya
matamikya.o: matamikya.c matamikya.h amount_set.h matamikya_print.h set.h
	gcc -c $(COMP_FLAG) matamikya.c
matamikya_product.o: matamikya_product.c matamikya_product.h
	gcc -c $(COMP_FLAG) matamikya_product.c 
matamikya_order.o: matamikya_order.c matamikya_order.h
	gcc -c $(COMP_FLAG) matamikya_order.c 
matamikya_print.o: matamikya_print.c matamikya_print.h
	gcc -c $(COMP_FLAG) matamikya_print.c 
matamikya_main.o: tests/matamikya_main.c
	gcc -c $(COMP_FLAG) tests/matamikya_main.c
matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h tests/test_utilities.h
	gcc -c $(COMP_FLAG) tests/matamikya_tests.c

amount_set_str: amount_set_str.o amount_set_str_list.o amount_set_str_main.o
	gcc amount_set_str.o amount_set_str_list.o amount_set_str_main.o -o amount_set_str
amount_set_str.o: amount_set_str.c amount_set_str.h amount_set_str_list.h
	gcc -c $(COMP_FLAG) amount_set_str.c
amount_set_str_main.o: tests/amount_set_str_main.c
	gcc -c $(COMP_FLAG) tests/amount_set_str_main.c
amount_set_str_list.o: amount_set_str_list.c amount_set_str_list.h
	gcc -c $(COMP_FLAG) amount_set_str_list.c
clean:
	rm -rf matamikya.o matamikya_product.o matamikya_order.o matamikya_print.o matamikya_tests.o matamikya_main.o amount_set_str.o amount_set_str_list.o amount_set_str_main.o matamikya amount_set_str

	