Masternode Budget API
=======================

Lunarium now supports full decentralized budgets that are paid directly from the blockchain via superblocks once per 30 days.

A GUI (graphical user interface) for the QT wallets are planned for those finding below a bit complex to comprehend.

Budgets go through a series of stages before being paid:
* prepare - create a special transaction that destroys 50 XLN coins in order to make a proposal
* submit - propagate transaction to peers on network
* voting - lobby for votes on your proposal
* get enough votes - make it into the budget
* finalization - at the end of each payment period, proposals are sorted then compiled into a finalized budget
* finalized budget voting - masternodes that agree with the finalization will vote on that budget
* payment - the winning finalized budget is paid


Prepare collateral transaction
------------------------

preparebudget \<proposal-name\> \<url\> \<payment_count\> \<block_start\> \<lunarium_address\> \<monthly_payment_lunarium\> [use_ix(true|false)]

Example:
```
preparebudget testing https://discord.gg/4nFZeJr 1 43200 LSZSmLaHy4D6M7PU9zhb7iBunGRRkauyqU 1000
```

Output: `fda9586854d1665e71f3783508b984299d096f2fe91c99654fe2a816675d5310` - This is the collateral hash, copy this output for the next step

In this transaction we prepare collateral for "testing". This proposal will pay _1000_ Lunarium, _1_ time totaling _1000_ Lunarium.

**Warning -- if you change any fields within this command, the collateral transaction will become invalid.**

Submit proposal to network
------------------------

submitbudget \<proposal-name\> \<url\> \<payment_count\> \<block_start\> \<lunarium_address\> \<monthly_payment_lunarium\> \<collateral_hash\>

Example:
```
submitbudget testing https://discord.gg/4nFZeJr 1 43200 LSZSmLaHy4D6M7PU9zhb7iBunGRRkauyqU 1000 fda9586854d1665e71f3783508b984299d096f2fe91c99654fe2a816675d5310
```

Output: `7321a7bc082f933f418563af872a21b9b5707ca386de33866dd36e486faaa49d` - This is your proposal hash, which other nodes will use to vote on it

Lobby for votes
------------------------

Double check your information:

mnbudget getinfo \<proposal-name\>

Example:
```
mnbudget getinfo testing
```
Output:
```
    "Name": "testing",
    "URL": "https://discord.gg/4nFZeJr",
    "Hash": "7321a7bc082f933f418563af872a21b9b5707ca386de33866dd36e486faaa49d",
    "FeeHash": "fda9586854d1665e71f3783508b984299d096f2fe91c99654fe2a816675d5310",
    "BlockStart": 43200,
    "BlockEnd": 86401,
    "TotalPaymentCount": 1,
    "RemainingPaymentCount": 1,
    "PaymentAddress": "LSZSmLaHy4D6M7PU9zhb7iBunGRRkauyqU",
    "Ratio": 1,
    "Yeas": 32,
    "Nays": 0,
    "Abstains": 0,
    "TotalPayment": 1000.00000000,
    "MonthlyPayment": 1000.00000000,
    "IsEstablished": true,
    "IsValid": true,
    "IsValidReason": "",
    "fValid": true
```

If everything looks correct, you can ask for votes from other masternodes. To vote on a proposal, load a wallet with _masternode.conf_ file. You should not access your cold wallet to vote for proposals.

mnbudgetvote "many" \<proposal_hash\> [yes|no]

Example:
```
mnbudgetvote "many" 7321a7bc082f933f418563af872a21b9b5707ca386de33866dd36e486faaa49d yes
```

Output: `"overall": "Voted successfully 10 time(s) and failed 0 time(s)."` - Your vote has been submitted and accepted.

Make it into the budget
------------------------

After you get enough votes, execute `mnbudget projection` to see if you made it into the budget. If you the budget was finalized at this moment which proposals would be in it. Note: Proposals must be active at least 1 day on the network and receive 10% of the masternode network in yes votes in order to qualify (E.g. if there is 500 masternodes, you will need 50 yes votes). Also need to have more yes than no votes.

Example:
```
mnbudget projection
```

Output:
```
 "Name": "testing",
    "URL": "https://discord.gg/4nFZeJr",
    "Hash": "7321a7bc082f933f418563af872a21b9b5707ca386de33866dd36e486faaa49d",
    "FeeHash": "fda9586854d1665e71f3783508b984299d096f2fe91c99654fe2a816675d5310",
    "BlockStart": 43200,
    "BlockEnd": 86401,
    "TotalPaymentCount": 1,
    "RemainingPaymentCount": 1,
    "PaymentAddress": "LSZSmLaHy4D6M7PU9zhb7iBunGRRkauyqU",
    "Ratio": 1,
    "Yeas": 32,
    "Nays": 0,
    "Abstains": 0,
    "TotalPayment": 1000.00000000,
    "MonthlyPayment": 1000.00000000,
    "IsEstablished": true,
    "IsValid": true,
    "IsValidReason": "",
    "fValid": true,
    "Alloted": 1000.00000000,
    "TotalBudgetAlloted": 1000.00000000
```

Finalized budget
------------------------

2880 blocks (about 48h) before the payout block is reached, a fee of 50 XLN to finalize the proposal is taken but for this to happen a wallet on the lunarium network needs to add `budgetvotemode=suggest` to `lunarium.conf`. This wallet also needs to be open, unlocked and have the 50 XLN for the finalization fee (+ minor transcation fee). If this fee can't be taken the proposal will fail and not pay out! Unless you have future budget blocks where you wish to pay this fee, it's recommended to remove `budgetvotemode=suggest` to avoid paying future finalization fees. The fee is taken for each and every budget block.

```
"main" : {
        "FeeTX" : "fda9586854d1665e71f3783508b984299d096f2fe91c99654fe2a816675d5310",
        "Hash" : "7321a7bc082f933f418563af872a21b9b5707ca386de33866dd36e486faaa49d",
        "BlockStart" : 43200,
        "BlockEnd" : 86401,
        "Proposals" : "testing",
        "VoteCount" : 32,
        "Status" : "OK"
    },
```

Get paid
------------------------

When block `43200` is reached you'll receive a payment of `1000` Lunarium.


RPC Commands
------------------------

The following RPC commands are supported:
- mnbudget "command"... ( "passphrase" )
 * preparebudget      - Prepare proposal for network by signing and creating tx
 * submitbudget       - Submit proposal for network
 * vote-many          - Vote on a Lunarium initiative
 * vote-alias         - Vote on a Lunarium initiative
 * vote               - Vote on a Lunarium initiative/budget
 * getvotes           - Show current masternode budgets
 * getinfo            - Show current masternode budgets
 * show               - Show all budgets
 * projection         - Show the projection of which proposals will be paid the next cycle
 * check              - Scan proposals and remove invalid

- mnfinalbudget "command"... ( "passphrase" )
 * vote-many   - Vote on a finalized budget
 * vote        - Vote on a finalized budget
 * show        - Show existing finalized budgets
