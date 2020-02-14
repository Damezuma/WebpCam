#pragma once
#include<wx/wx.h>
wxDECLARE_EVENT(EVT_CompleteRecord, wxCommandEvent);
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
//�̹����� �ִϸ��̼� �̹����� ����� �������̽�
wxDECLARE_EVENT(EVT_FINISH_ENCODE, wxCommandEvent);//���ڵ��� �Ϸ����� ��
wxDECLARE_EVENT(EVT_FAILED_ENCODE, wxCommandEvent);//���ڵ��� �������� ��
wxDECLARE_EVENT(EVT_ADDED_A_FRAME, wxCommandEvent);//������ �ϳ��� ó�� �Ϸ� ���� ��
//TODO: webp �̿��� �̹��� ������ �����غ���.
struct IEncoder
{
	virtual void Encode(wxEvtHandler * handler, const wxString filePath, const IImageStore& imageStore) = 0;
	virtual wxString GetFileFilter() =0;
	virtual wxString GetFileExtension() = 0;
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
