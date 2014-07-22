/*******************************************************************************
    OpenAirInterface
    Copyright(c) 1999 - 2014 Eurecom

    OpenAirInterface is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.


    OpenAirInterface is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with OpenAirInterface.The full GNU General Public License is
    included in this distribution in the file called "COPYING". If not,
    see <http://www.gnu.org/licenses/>.

  Contact Information
  OpenAirInterface Admin: openair_admin@eurecom.fr
  OpenAirInterface Tech : openair_tech@eurecom.fr
  OpenAirInterface Dev  : openair4g-devel@eurecom.fr

  Address      : Eurecom, Compus SophiaTech 450, route des chappes, 06451 Biot, France.

*******************************************************************************/

#    ifndef _TRANSACTIONS_H
#        define _TRANSACTIONS_H

#        include <map>
#        include "Message.h"
#        include "Transaction.h"
#        include "platform.h"
using namespace std;

class Transactions  {
    public:

        static Transactions *Instance ();
        ~Transactions ();

        bool    IsTransactionRegistered(transaction_id_t idP);
        void    AddTransaction(Transaction* txP);
        void    RemoveTransaction(transaction_id_t idP);
        Transaction* const GetTransaction(transaction_id_t idP);

    private:
        Transactions ();

        static Transactions                *s_instance;
        map<transaction_id_t,Transaction*>  m_transaction_map;
};
#    endif

