//
// Created by Ziv on 02/07/2021.
//
#include "examDetails.h"
namespace mtm
{
    ExamDetails:: ExamDetails(const int course_number, const int month, const int day_of_exam, const double hour_of_exam,
                         const int length_of_exam, const string &link_to_zoom ) : course_number(course_number),
                                                                                      month(month),
                                                                                      day_of_exam(day_of_exam),
                                                                                      hour_of_exam(hour_of_exam),
                                                                                      length_of_exam(
                                                                                              length_of_exam),
                                                                                      link_to_zoom(link_to_zoom) {
        if (!(course_number > 0)) throw InvalidArgsException();
        if (!(month >= 1 && month <= 12) || !(day_of_exam >= 1 &&
                                              day_of_exam <= 30))
            throw InvalidDateException();
        double *y = new double;
        *y = 1;
        if (!(modf(length_of_exam, y) == 0 || !(modf(hour_of_exam, y) == 0 || modf(hour_of_exam, y) == 0.5))) {
            delete y;
            throw InvalidTimeException();
        }

        delete y;
    }
    int ExamDetails::getHour() const
    {
        double hour(this->hour_of_exam);//create copy
        int hour_returned=(int)floor(hour);
        return hour_returned;
    }
    string ExamDetails::getMintues() const
    {
        double* y=new double;
        *y=1;
        double remainder=modf(this->hour_of_exam,y);
        if(remainder==0)
        {
            delete y;
            return "00";
        }
        else {
            delete y;
            return "30";
        }
    }
    string ExamDetails::getLink() const {
        const string str = this->link_to_zoom;
        return str;
    }

    void ExamDetails::setLink(const string &link) {
        this->link_to_zoom = link;
    }

    int ExamDetails::operator-(const ExamDetails &exam) const {
        return (this->day_of_exam - exam.day_of_exam) + ((this->month - exam.month) * DAYS_IN_MONTH);
    }

    bool ExamDetails::operator<(const ExamDetails &exam) const {
        int day_diff = this->operator-(exam);
        if (day_diff < 0) return true;
        if (day_diff == 0) {
            if (this->hour_of_exam - exam.hour_of_exam >= 0)
                return false;//its the same day,but leftexam starts later or at same time as rightexam
            else return true;
        } else return false;//only condition left is when day_diff>0,and its false.
    }

ostream & operator<<(ostream &os, const ExamDetails &exam) {
    os << "Course Number: " << exam.course_number << endl;
    os << "Time: " << exam.day_of_exam << "." << exam.month << " at " << exam.getHour()
       <<":"<<exam.getMintues() << endl; /*need to get changed,for now,good enoguh*/
    os << "Duration: " << exam.length_of_exam << ":00"<< endl;
    os << "Zoom Link: " << exam.link_to_zoom << endl;
    return os;
}

bool ExamDetails::operator==(const ExamDetails &examDetails) const {
    return (month == examDetails.month && day_of_exam == examDetails.day_of_exam &&
            hour_of_exam == examDetails.hour_of_exam && length_of_exam == examDetails.length_of_exam
            && link_to_zoom==(examDetails.link_to_zoom));
}
}
