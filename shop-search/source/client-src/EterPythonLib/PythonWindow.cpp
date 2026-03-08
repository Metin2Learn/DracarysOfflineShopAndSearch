# Search

	BOOL CImageBox::LoadImage(const char * c_szFileName)

# Add before

	BOOL CImageBox::LoadImage(CGraphicImageInstance* imageInstance)
	{
		if (!imageInstance)
			return FALSE;
		OnCreateInstance();
		m_pImageInstance->SetImagePointer(static_cast<CGraphicImage*>(imageInstance->GetGraphicImagePointer()));
		if (m_pImageInstance->IsEmpty())
			return FALSE;
		SetSize(m_pImageInstance->GetWidth(), m_pImageInstance->GetHeight());
		UpdateRect();
		CGraphicImageInstance::Delete(imageInstance);
		return TRUE;
	}