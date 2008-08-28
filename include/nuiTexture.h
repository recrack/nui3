/*
  NUI3 - C++ cross-platform GUI framework for OpenGL based applications
  Copyright (C) 2002-2003 Sebastien Metrot

  licence: see nui3/LICENCE.TXT
*/

#ifndef __nuiTexture_h__
#define __nuiTexture_h__

//#include "nui.h"
#include "nglImageCodec.h"
#include "nuiObject.h"
#include "nuiRefCount.h"

#include <map>

class nuiTexture;
class nuiPainter;
class nuiTextureCache;
class nuiSurface;

typedef std::map<nglString, nuiTexture*, nglString::LessFunctor> nuiTextureMap;
typedef std::set<nuiTextureCache*> nuiTextureCacheSet;

/// This class implements a basic image widget.
class NUI_API nuiTexture : public nuiObject, public nuiRefCount
{
public:
  // Constructors and destructors are protected!
  static nuiTexture* GetTexture (nglIStream* pInput, nglImageCodec* pCodec = NULL); ///< Create an image from an input stream and a codec.  If \param pCodec is NULL all codecs will be tried on the image.
  static nuiTexture* GetTexture (const nglPath& rPath, nglImageCodec* pCodec = NULL ); ///< Create an image from a path and a codec. If \param pCodec is NULL all codecs will be tried on the image.
  static nuiTexture* GetTexture (nglImageInfo& rInfo, bool Clone = true); ///< Create an image from an nglImageInfo structure. If \param is true then the image buffer will be cloned, otherwise it will be deleted with the nuiTexture.
  static nuiTexture* GetTexture (const nglImage& rImage); ///< Create an image by copying an existing nglImage.
  static nuiTexture* GetTexture (nglImage* pImage, bool OwnImage); ///< Create an image from an existing nglImage. If \param OwnImage the nglImage object will be deleted with the nuiTexture.
  static nuiTexture* GetTexture (const nuiXMLNode* pNode); ///< Create an image from an xml description.
  static nuiTexture* GetTexture (const nglString& rName); ///< Get a texture from its ID only
  static nuiTexture* GetTexture (nuiSurface* pSurface, bool OwnSurface); ///< Create a texture from an existing nuiSurface. . If \param OwnImage the nuiSurface object will be deleted with the nuiTexture.

  static void ClearAll();
  static void ForceReloadAll(bool Rebind = false);

  virtual nuiXMLNode* Serialize(nuiXMLNode* pParentNode, bool Recursive) const;

  void ForceReload(bool Rebind = false); ///< This method deletes the texture assiciated with the nuiTexture thus forcing its recreation at the next rendertime. If Rebind == false then we consider that the native (GL) texture was lost because the context/window have been destroyed and we have to completely recreate the texture.
  void ResetForceReload();
  void ImageToTextureCoord(nuiSize& x, nuiSize& y) const; ///< Transform the x,y point in the coordinates of the image to the coordinates of the texture. 
  void TextureToImageCoord(nuiSize& x, nuiSize& y) const; ///< Transform the x,y point in the coordinates of the texture to the coordinates of the image. 
  void ImageToTextureCoord(nuiAltSize& x, nuiAltSize& y) const;
  void TextureToImageCoord(nuiAltSize& x, nuiAltSize& y) const;

  nglImage* GetImage() const; ///< Return a pointer to the nglImage contained in this object.
  void      ReleaseBuffer(); ///< Release the image source

  GLuint GetMinFilter() const; ///< Get the maximization filter
  GLuint GetMagFilter() const; ///< Get the minimization filter
  GLuint GetWrapS() const;     ///< Get the S coord wrap rule.
  GLuint GetWrapT() const;     ///< Get the T coord wrap rule.
  GLuint GetEnvMode() const;   ///< Get the environement mode.

  uint32 GetWidth() const;
  uint32 GetHeight() const;
  uint32 GetWidthPOT() const;
  uint32 GetHeightPOT() const;
  
  void SetMinFilter(GLuint Filter);  ///< Set the maximization filter
  void SetMagFilter(GLuint Filter);  ///< Set the minimization filter
  void SetWrapS(GLuint WrapS);       ///< Set the S coord wrap rule.
  void SetWrapT(GLuint WrapT);       ///< Set the T coord wrap rule.
  void SetEnvMode(GLuint Mode);      ///< Set the environement mode.

  void SetRetainBuffer(bool Retain); ///< Set the nglImage destroying switch upon uploading to OpenGL

  bool SetSource(const nglString& rName); ///< Set the image source. Permits to set a global name for an image source instead of the automatically assigned one.
  nglString GetSource() const; ///< Retreive the source name of this texture.

  static void SetSharedContext(nglContext* pContext); ///< This method sets the shared context used to store texture over multiple renderers. It should be only called once per application.
  
  bool IsUptoDate() const { return !mForceReload; }
  bool IsPowerOfTwo() const; // Returns true if the width and the height of the texture are powers of two.
  bool IsBufferRetained() const { return mRetainBuffer; } ///< returns true if the texture doesn't try to destroy the image source upon uploading to OpenGL

  static void AddCache(nuiTextureCache* pCache);
  static void DelCache(nuiTextureCache* pCache);
  
protected:
  nuiTexture(nglIStream* pInput, nglImageCodec* pCodec = NULL); ///< Create an image from an input stream and a codec.  If \param pCodec is NULL all codecs will be tried on the image.
  nuiTexture(const nglPath& rPath, nglImageCodec* pCodec = NULL ); ///< Create an image from a path and a codec. If \param pCodec is NULL all codecs will be tried on the image.
  nuiTexture(nglImageInfo& rInfo, bool Clone = true); ///< Create an image from an nglImageInfo structure. If \param is true then the image buffer will be cloned, otherwise it will be deleted with the nuiTexture.
  nuiTexture(const nglImage& rImage); ///< Create an image by copying an existing nglImage.
  nuiTexture(nglImage* pImage, bool OwnImage); ///< Create an image from an existing nglImage. If \param OwnImage the nglImage object will be deleted with the nuiTexture.
  nuiTexture(const nuiXMLNode* pNode); ///< Create an image from an xml description.
  
  virtual ~nuiTexture();
  void Init();

  nglImage* mpImage;
  bool mOwnImage;
  nuiSize mRealWidth;
  nuiSize mRealHeight;
  nuiSize mRealWidthPOT;
  nuiSize mRealHeightPOT;
  bool mForceReload;
  bool mRetainBuffer;

  GLuint mMinFilter;
  GLuint mMagFilter;
  GLuint mWrapS;
  GLuint mWrapT;
  GLuint mEnvMode;

  static nglContext* mpSharedContext;
  static nuiTextureMap mpTextures;
  static nuiTextureCacheSet mTextureCaches;
};

class nuiTextureCache
{
public:
  nuiTextureCache();
  virtual ~nuiTextureCache();
  
  virtual void CreateTexture(nuiTexture* pTexture);
  virtual void DestroyTexture(nuiTexture* pTexture);
  virtual void InvalidateTexture(nuiTexture* pTexture, bool ForceReload);
};



#endif // __nuiTexture_h__
