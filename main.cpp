#include <iostream>

#include "multiplication/Multiplication.h"

#include "cook/float_cook.h"
#include "cook/division_cook.h"

#include "prime/Prime.h"

std::ostream &operator<<(std::ostream &output, TInteger a) {
    return output << (std::string)a;
}

int main() {
    TInteger a(123), b("456");

    // Should output:
    // 56088
    // 59932
    // 54321
    // 33141
    //
    // *output for the next tests*

    // It means, that all methods have been used

    Multiplication* multiply_method = new Karatsuba;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new TomCook;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new Modular;
    std::cout << multiply_method->multiply(a, b) << "\n";

    multiply_method = new SchonhageShtrassen;
    std::cout << multiply_method->multiply(a, b) << "\n\n";

    std::cout << a * b << "\n"; // 123 * 456 = 56088

    TInteger c("21474836470");

    std::cout << (int)c << "\n";

    std::vector<TInteger> parts = c.split(8, 3);
    for (int i = 0; i < parts.size(); i++) {
        std::cout << parts[i] << ' ';
    }
    std::cout << "\n";

    a = TInteger("-561268018958885834580935165168413175695260534304988985072379284906900136552453417828631038613958358567017852892164560354705052957630645581524066850593313596814578772308167705308820445847115977895782994118379504030389806343607369250791140582520873778634572782817974162670810579923113997609116071651185205109336335845605570169189485710698035479661227275059421836100541252494809862059055589239803379777576594958225531312986522848116572020574047360840918891576191839298239067142027902029602443570998529568546363910440243898621348642837703026330654176477457567555534021309788930637833030686250734998774455547631290097158188935920335774818510605661145720511915719079311682378912549332457197689811519977885582863762670835932706778320670613849943920492036815219980472854554738646101127236866607483094343921017626384308747830449786697986411307989304471476721057866174734859889533421295468855650434238711535190724137807035400740032674922536233167334660210179753537148666382243656898936228234143233995947132");
    TInteger divider(-29157045);
    std::cout << a / divider << "\n";

    return 0;
}