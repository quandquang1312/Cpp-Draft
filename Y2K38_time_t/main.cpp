#include "utils.cpp"
#include "replace_solution.cpp"

int main(int argc, char* argv[]) {
    auto tp = std::chrono::system_clock::now();
    auto tp2040 = createTimePoint(2040, 1, 19, 3, 14, 7);

    int year = (argc > 1 ? atoi(argv[1]) : 1000); 

    // Checking custom conversion from 64b to 32b
    time_32t timeInMyTimeT = toMyTimeT(tp);
    time_32t timeInMyTimeCustom = toMyTimeT(tp);
    std::cout << "Time in 32-bit time_t: " << timeInMyTimeT << std::endl;
    std::cout << "Custom time in 32-bit time_t: " << timeInMyTimeCustom << std::endl;

    //
    std::string time_str  = getIso8601UtcTimeStamp(tp);
    std::string time_str2 = getIso8601UtcTimeStamp_r(tp);

    std::cout << "Time_str 2040: " << time_str.c_str() << std::endl;
    std::cout << "Replaced 2040: " << time_str2.c_str() << std::endl;

    // Validating
    int match = 0, total = 0;
    for (int y=LOWER_YEAR; y<=LOWER_YEAR + year; y++) {
        for (int m=1; m<=12; m++) {
            std::cout << y << "_" << m << ": ";
            std::cout << "not math: " << total - match << ", " << match << "/" << total << std::endl;
            int day_lim = -1;
            if (m == 2) {
                if (isLeapYear(y)) day_lim = 29;
                else day_lim = 28;
            } else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) day_lim = 31;
            else day_lim = 30;

            for (int d=1; d<=day_lim; d++) {
                // std::cout << d << "_ " << std::endl;
                for (int h=0; h<=23; h++) {
                    for (int mi=0; mi<60; mi++) {
                        for (int s=0; s<60; s++) {
                            auto tp = createTimePoint(y, m, d, h, mi, s);

                            std::string original_time_str = getIso8601UtcTimeStamp(tp);
                            std::string replaced_time_str = getIso8601UtcTimeStamp_r(tp);

                            if (original_time_str.compare(replaced_time_str) == 0) {
                                match++;
                            } else {
                                if (total % 100000 == 0) {
                                    std::cout << original_time_str.c_str() << " - " << replaced_time_str.c_str() << std::endl;
                                }
                            }

                            total++;
                        }
                    }
                }
            }
        }
    }

    std::cout << match << "/" << total << std::endl;

    return 0;
}