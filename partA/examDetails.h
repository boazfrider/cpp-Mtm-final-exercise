#include <iostream>
#include <string>
#include <cmath>

#ifndef EXAMDETAILS_H
#define EXAMDETAILS_H
#define DAYS_IN_MONTH 30
#define MATAM_EXAM_LINK "https://tinyurl.com/59hzps6m"
#define MATAM_EXAM_COURSE_NUMBER 234124
#define MATAM_EXAM_DAY 28
#define MATAM_EXAM_HOUR 13.00
#define MATAM_EXAM_TEST_LENGTH 3
#define MATAM_EXAM_MONTH 7

namespace mtm {
    enum month {
        JANUARY = 1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER
    };
    using std::string;
    using std::ostream;
    using std::modf;
    using std::endl;
    using std::cout;


    class ExamDetails {
    private:
        int course_number;
        int month;
        int day_of_exam;//need to get only 1-30- by set function.
        double hour_of_exam;//need to be xx(0-23):xx(00,30)
        int length_of_exam;//has to be in complete hours(1,2,3,4..eg..there is no limitation(could be 231221 hours for ex))
        string link_to_zoom;


    public:
        /*
        *InvalidDateExeption-  happend when the the date is not valid.
        */
        class InvalidDateException {
        };

        /*
        InvalidTimeException - the time is not valid.
        */
        class InvalidTimeException {
        };

        /*
        InvalidArgsException - happend when other of the parameter went wrong.
        */
        class InvalidArgsException {
        };

        /*ExamDetails - create a new object of exam.
        @param course_number- the number of the course.
        @param month- the month that the test is happend.
        @param day_of_exam- the day in the month. number between 1 to 30.
        @param hour_of_exam- the start time for the test , hour: 0 -23 , min:00/30.
        @param-length_of_exam -time in hour.
        @param &link_to_zoom-a string that represent the URL for the zoom link.
        */
        explicit ExamDetails(const int course_number, const int month, const int day_of_exam, const double hour_of_exam,
                             const int length_of_exam, const string &link_to_zoom = "");

        /*~ExamDetails - the distrctor, default.
        */
        ~ExamDetails() = default;

        ExamDetails(const ExamDetails &exam) = default;

        /*operator== : comparing between two tests.
        @return true - the exams are equal.
        @return false- exams not equal.
        */
        bool operator==(const ExamDetails &examDetails) const;

        
        /*getHour-return the Hour
        */
        int getHour() const;

        /*getMintues- return the mintues.
        */
        string getMintues() const;


        /* function- getLink 
        * no param
        *@return link to the exam.
        */
        string getLink() const;

        /*setLink - set a new link to the exam.
        *@param - the current link.
        *@return- void.
        */
        void setLink(const string &link);

        /*operator- : operator that count the diffrence days between the test.(left-right)
        *@param - 2 exams.
        *@return the diffrence days.
        */
        int operator-(const ExamDetails &exam) const;

        /*operator < : check if the left test happend after the left test
        *@return true- the left test happend before the right test.
        *return false- if the test are simulatny.
        */
        bool operator<(const ExamDetails &exam) const;

        ExamDetails &operator=(const ExamDetails &exam1) = default;

        static ExamDetails makeMatamExam() {
            ExamDetails Exam(MATAM_EXAM_COURSE_NUMBER, MATAM_EXAM_MONTH, MATAM_EXAM_DAY, MATAM_EXAM_HOUR,
                             MATAM_EXAM_TEST_LENGTH, MATAM_EXAM_LINK);
            return Exam;
        }

        /* operator<< : function to print the deatial.
        *@param &os - the address print.
        @param exam - the exam we need to print.
        */
        friend   ostream &operator<<(ostream &os, const ExamDetails &exam);
    };
}
#endif