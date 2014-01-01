
- MSG sending entity which takes in a standardized message from
- MSG creation entity which responds to changes in those contents:
- Kill, User, Msg when specific actions happen:
- Kill, Accept, Deny, Target Assign, Suspend, News

Kill & Accept & Deny    -   Kill
Target Assign & Suspend -   User
Question & News         -   Message

Actions:
Kill create             -   Create message to target
Kill update             -   Comment message to assassin/target
User update             -   Create message to user
Message creation        -   Send email/sms appropriately 