#include "wx/wxprec.h"
#include "webpencoder.h"
#include "webp/encode.h"
#include <wx/wfstream.h>
#include <wx/time.h>

#pragma comment(lib,"libwebp.lib")
#pragma comment(lib,"libwebpdemux.lib")
#pragma comment(lib,"libwebpmux.lib")

void WebpEncoder::Encode(wxEvtHandler* handler, const wxString filePath, const IImageStore& imageStore)
{
	WebPConfigInit(&m_config);
	WebPAnimEncoderOptionsInit(&m_encoderOption);
	auto image = imageStore[0].first;
	uint32_t width = image.GetWidth();
	uint32_t height = image.GetHeight();
	uint32_t timestamp = 0;
	//WebP Config����
	m_config.quality = 80.f;
	m_config.thread_level = 1;//��Ƽ ������ ���
	m_config.lossless = 0;//�ս�����
	m_config.low_memory = 0;
	m_config.filter_strength = 0;//���� �� �𸣰ڽ� 
	m_config.method = 6;//����� �ִ�
	//Ű������ �ּҿ� �ִ�;
	m_encoderOption.kmin = 1;
	m_encoderOption.kmax = 40;
	//���ڴ��� �ʱ�ȭ
	m_encoder = WebPAnimEncoderNew(width, height,&m_encoderOption);
	//�������� �ʱ�ȭ�Ѵ�
	WebPPictureInit(&m_frame);
	m_frame.width = width;
	m_frame.height = height;
	m_frame.use_argb = 1;
	WebPPictureAlloc(&m_frame);
	for(int i = 0 ; i < imageStore.GetSize(); i++)
	{
		auto data = imageStore[i];
		auto rgbData = data.first.GetData();
		WebPPictureImportRGB(&m_frame, rgbData, 3 * m_frame.width);
		WebPAnimEncoderAdd(m_encoder, &m_frame, timestamp, &m_config);
		timestamp += data.second;

		auto* event = new wxCommandEvent(EVT_ADDED_A_FRAME);
		event->SetInt(i);
		handler->QueueEvent(event);
	}

	WebPData webpData;
	WebPDataInit(&webpData);
	//������ NULL�������� ����ִ´�.
	WebPAnimEncoderAdd(m_encoder, nullptr, timestamp, nullptr);
	WebPAnimEncoderAssemble(m_encoder, &webpData);

	auto webpMux = WebPMuxCreate(&webpData, 1);
	WebPDataClear(&webpData);
	WebPMuxAssemble(webpMux, &webpData);

	wxFileOutputStream* wfos = new wxFileOutputStream(filePath);
	wfos->WriteAll(webpData.bytes, webpData.size);
	wfos->Close();
	delete wfos;
	WebPPictureFree(&m_frame);
	WebPDataClear(&webpData);
	WebPMuxDelete(webpMux);
	WebPAnimEncoderDelete(m_encoder);

	auto* event = new wxCommandEvent(EVT_FINISH_ENCODE);
	handler->QueueEvent(event);
}

wxString WebpEncoder::GetFileFilter()
{
	//TODO:
	return wxString();
}

wxString WebpEncoder::GetFileExtension()
{
	return wxT("webp");
}
