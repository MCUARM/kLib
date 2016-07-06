#ifndef __kClient_H
#define __kClient_H

	#define kClient_RX_BUFFER_SIZE 256
	#define kClinet_TX_BUFFER_SIZE 256

	#include "kSystem.h"

	class kClient : public kSerial
	{
		private:

			char cli_rxBuffer[kClient_RX_BUFFER_SIZE];
			char cli_txBuffer[kClinet_TX_BUFFER_SIZE];

			void sendResponse(char * buffer);

		public:

			kClient(void);
			void check(void);
			void run(unsigned int BaudRate);

	};

#endif
