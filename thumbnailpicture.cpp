#include "thumbnailpicture.h"

ThumbnailPicture::ThumbnailPicture()
{
    this->setMaximumSize(ThumbnailPicture::MAX_WIDTH, ThumbnailPicture::MAX_HEIGHT);
}

ThumbnailPicture::ThumbnailPicture(QPixmap pixmap) {
    this->setPixmap(pixmap);
    this->setMaximumSize(ThumbnailPicture::MAX_WIDTH, ThumbnailPicture::MAX_HEIGHT);
}

ThumbnailPicture::~ThumbnailPicture()
{

}

