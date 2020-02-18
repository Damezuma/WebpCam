﻿#pragma once
#include "interface.h"
#include <wx/zstream.h>
#include <wx/wfstream.h>
#include <wx/msgqueue.h>
#include <vector>
#include <array>
#include <wx/filename.h>
#include <wx/mstream.h>
class CISSaveThread : public wxThreadHelper
{
	wxFileOutputStream& m_fOStream;
	std::vector<size_t>& m_bytesCounts;
	wxMessageQueue<std::pair<wxImage*, uint32_t>>& m_mqueue;
public:
	CISSaveThread(
		wxFileOutputStream& fOStream,
		std::vector<size_t>& offsets,
		wxMessageQueue<std::pair<wxImage*, uint32_t>>& mqueue);
protected:
	void* Entry() override;
};
class CachedImageStorageBuilder : public IImageStoreBuilder
{
public:
public:
	CachedImageStorageBuilder(const wxSize& imageSize);
	~CachedImageStorageBuilder();
	virtual void PushBack(const wxImage& image, uint32_t duration) override;
	virtual size_t GetSize() const override;
protected:
	virtual IImageStore* BuildStore() override;

private:
	wxSize m_imageSize;
	std::vector<uint32_t> m_durations;
	std::vector<size_t> m_bytesCounts;
	wxMessageQueue<std::pair<wxImage*, uint32_t>> m_mqueue;
	CISSaveThread m_backgroundThread;
	wxString m_fileName;
	wxFileOutputStream m_fileOStream;
};