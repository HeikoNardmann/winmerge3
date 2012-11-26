#ifndef DIRCOMPARE_H
#define DIRCOMPARE_H

#include <QList>
#include "comparison.h"

#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>

class QString;
class QDir;

class DirCompare : boost::noncopyable
{
public:
    DirCompare(const QString &item1, const QString &item2);
    ~DirCompare();

    void DoCompare();
    QList<Comparison> GetResults() const;

private:
    typedef boost::scoped_ptr<QDir> qdir_holder_t;
    qdir_holder_t mDir1;
    qdir_holder_t mDir2;
    QList<Comparison> mResults;
};

#endif // DIRCOMPARE_H
