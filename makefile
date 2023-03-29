cc = g++
SRC = ./src
FLAGS = -fPIC
MEMORY_LOG = ./thrid_lib/memory_log
DLL_LIB = ./thrid_lib/ctp_linux_lib
OUTPUT = ./output
INCLUDE =./thrid_lib/ctp_linux_lib -I ./src  -I./ -I $(MEMORY_LOG)
test_ctp: $(SRC)/main.cpp market ctp_md_lib ctp_trader_lib
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/code/my_trade/output
	mv *.o $(OUTPUT)/
	$(cc) -o $(OUTPUT)/test_ctp.o $(SRC)/main.cpp  $(OUTPUT)/market.o $(OUTPUT)/market_api.o $(OUTPUT)/memory_log.o  $(FLAGS) -I $(INCLUDE) -L$(DLL_LIB) -lthostmduserapi_se -lthosttraderapi_se
	$(OUTPUT)/test_ctp.o
market: $(SRC)/market.cpp  market_api  memory_log  output
	$(cc) -c $(SRC)/market.cpp -I $(INCLUDE)
market_api:$(SRC)/market_api.cpp output
	$(cc) -c $(SRC)/market_api.cpp -I $(INCLUDE)
memory_log:$(MEMORY_LOG)/memory_log.cpp $(MEMORY_LOG)/memory_log.h output
	$(cc) -c $(MEMORY_LOG)/memory_log.cpp -I $(MEMORY_LOG)
output:
	mkdir output
ctp_md_lib: $(DLL_LIB)/libthostmduserapi_se.so
ctp_trader_lib: $(DLL_LIB)/libthosttraderapi_se.so
.PHYONE: ctp_md_lib ctp_trader_lib output
clean:
	rm  *.o $(OUTPUT)/*.o *.con