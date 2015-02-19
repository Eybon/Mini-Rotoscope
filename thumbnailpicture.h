#ifndef THUMBNAILPICTURE_H
#define THUMBNAILPICTURE_H

#include <QLabel>
#include <QPixmap>

class ThumbnailPicture : public QLabel
{
public:
    ThumbnailPicture();
    ThumbnailPicture(QPixmap);
    ~ThumbnailPicture();


private:
    const static int MAX_HEIGHT = 200;
    const static int MAX_WIDTH = 200;
};

#endif // THUMBNAILPICTURE_H
