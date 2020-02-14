#pragma once
#include<wx/wx.h>
wxDECLARE_EVENT(EVT_CompleteRecord, wxCommandEvent);
//�̹����� �ִϸ��̼� �̹����� ����� �������̽�
//TODO: webp �̿��� �̹��� ������ �����غ���.
struct IEncoder
{
	virtual bool BeginEncode(wxEvtHandler * handler, uint32_t width, uint32_t height) = 0;
	virtual bool AddFrame(const wxImage& frame, uint32_t duration) = 0;
	virtual bool EndEncode() = 0;
	virtual ~IEncoder() {}
};
//ȭ���� ĸ���ϴ� �������̽�
//TODO: DirectX�� �̿��� ĸó Ŭ������ �����.
struct ICapturer
{
	virtual void BeginCapture(wxEvtHandler* handler, const wxRect& rect, uint32_t duration) = 0;
	virtual std::pair<wxImage, uint32_t> CaptureFrame() = 0;
	virtual void EndCapture() = 0;
	virtual ~ICapturer() {}
};
//ĸó �̹��� �����͸� �ӽ÷� �����ϴ� --�������̽�-- �߻�Ŭ����
struct IImageStore
{
	virtual ~IImageStore() {}
	virtual size_t Add(const wxImage& image, uint32_t duration) = 0;
	virtual const std::pair<wxImage, uint32_t> Get(size_t index) const = 0;
	virtual size_t GetSize() const = 0;
	virtual void Clear() = 0;
	size_t size()
	{
		return GetSize();
	}
	const std::pair<wxImage, uint32_t> operator[] (size_t index) const
	{
		return Get(index);
	}
};