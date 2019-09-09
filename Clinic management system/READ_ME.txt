The program ran with a db file containing 2 therapists, 2 patients, 2 secretaries, 2 appointments.

After reading from the file, a menu opens:
1.LOGIN- Enter an ID and a menu will open according to the job
2.SIGNUP- Option to add a new user (user type (1-for therapist 2-for patient, 3-for secretary), age, first name, last name, ID)
3.CLOSE - Closes the program after all the changes and writes the information back to db


The call from the session status file is called as number and then sorted to its type in the object. As a write-to-file, it is written as a number to allow convenient file reuse.