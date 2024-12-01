#include <QtCore>
#include <algorithm>    

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    // Get input file
    QFile inputFile = QFile("input.txt");
    if(!inputFile.open(QFile::OpenModeFlag::ReadOnly | QFile::OpenModeFlag::Text))
    {
        qDebug() << "Could not open file";
    }

    // Read input
    QList<int> listA;
    QList<int> listB;
    QList<int> distance;
    int simScore = 0;
    while(!inputFile.atEnd())
    {
        // Read contents
        QString inputLine = inputFile.readLine();

        // Split string
        auto sections = inputLine.split("   ");
        if(sections.size() != 2)
        {
            qWarning() << "Something is wrong here!";
        }

        // Add contents to list
        listA.append(sections.first().toInt());
        listB.append(sections.last().toInt());
    }

    // Sort the list
    std::sort(listA.begin(), listA.end());
    std::sort(listB.begin(), listB.end());

    // Check the list sizes, just to be sure
    if(listA.size() != listB.size())
    {
        qWarning() << "The lists are not of the same lenght, what have you done!";
    }

    // Calculate the distance
    for(int i = 0; i < listA.size(); i++)
    {
        // Calculate distance
        distance.append(abs(listA.at(i) - listB.at(i)));

        // Calculate similarity 
        auto occurance = std::count(listB.constBegin(), listB.constEnd(), listA.at(i));
        simScore += (occurance * listA.at(i));
    }

    // Print bags
    auto sum = std::accumulate(distance.constBegin(), distance.constEnd(), 0);
    qDebug() << "Distance:" << sum << '\n';
    qDebug() << "Similarity:" << simScore << '\n';
    
    return a.exec();
}
