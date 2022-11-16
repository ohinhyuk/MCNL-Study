/*

Implement a simple Bayesian Spam filter and determine if each email in 'test' folder is spam or ham.
- In 'train' folder, two files contain 100 spam and 100 non-spam messages.
- In 'test' folder, two files contain 20 spam and 20 non-spam messages.
- We want to classify 40 emails in 'test' folder based on the emails in 'train' folder.
- Thus, probabilies should be calcualted from emails in 'train' folder.
- Please ignore all special characters(e.g. '~!@#$%^&*()-<>?/ .... )
- Use C or C++. No other programming language (ex. python, Java etc)


[Procedue for decision.]
Per each email from test forder
	calculate r(w1, ...... , wn) and apply a threshold.
	assign label (spam or non-spam) which is a predicted label.


Caclualte accuracy of your prediction.
(the number of correctly classiferd test emails) divided by 40.
- since we have 40 test emails (20 spam and 20 non-spam).


For fun, let's try various 'threshold (T)' for decision.
T = 0.6, 0.7, 0.8, 0.9, 0.95.
This means that we will have 5 accuracies.


* What to submit.
- Your C code. (it should be ready for excution, TA will test it.)
- Report (attached in the notice).
- Zip your report and your code (.c) and submit.



Deadline: 11.30(Wed) 23:00

*/