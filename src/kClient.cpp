#include "kClient.h"

#if (kLib_config_USE_MODULE == 1)

	kClient::kClient(void)
	{

	}
	void kClient::run(unsigned int BaudRate)
	{
		this->terminator('\r');
		kSerial::run(BaudRate);
	}

	void kClient::check(void)
	{
		unsigned short int i;
		char * pBuffer;
		kRegister * systemReg;
		kModule * module;
		char module_id;

		if(!this->newDataAvailable()) return;

		i = this->readData(this->cli_rxBuffer);
		this->cli_rxBuffer[i]=0;

		pBuffer = kString::skipWhiteSpace(cli_rxBuffer);
		if(!(*pBuffer))
		{
			this->sendResponse(cli_txBuffer);
			return;
		}

		if(kString::firstWordCompare(pBuffer,"system"))
		{
			pBuffer = kString::skipOneWord(pBuffer);
			if(!(*pBuffer))
			{
				this->sendResponse(cli_txBuffer);
				return;
			}
			pBuffer = kSystem.processCommand(pBuffer,cli_txBuffer);
		}else
		{
			systemReg = kSystem.getSystemRegister();
			module_id = systemReg->findByName(cli_rxBuffer);

			if(module_id >= 0)
			{
				module = systemReg->at(module_id);
				pBuffer = module->processCommand(pBuffer,cli_txBuffer);
			}else
			{
				pBuffer = kString::copy("Unresolved module",cli_txBuffer);
			}

		}


		this->sendResponse(pBuffer);


	}
	void kClient::sendResponse(char * buffer)
	{
		buffer = kString::copy("\rkSystem > ",buffer);
		*buffer = 0;
		(*this) << cli_txBuffer;
	}

#endif
