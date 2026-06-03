#pragma once
#include "LibGraph2.h"

class CObjetGraphique
{
private:
	//COULEURS
	LibGraph2::ARGB m_colColor = 0xFF000000;
	LibGraph2::ARGB m_colFillColor = 0xFFFF0000;
	LibGraph2::ARGB m_baseColFillColor = 0xFFFF0000;
	//EPAISSEUR
	float m_fThickness = 1.0f;
	//STYLE
	LibGraph2::pen_DashStyles m_eStyle = LibGraph2::pen_DashStyles::Solid;
protected:
	LibGraph2::CPoint m_ptP1 = LibGraph2::CPoint(0, 0);
public:
	virtual void Afficher(bool sombre) const;

	//GETTERS
	LibGraph2::ARGB GetColor() const { return m_colColor; }
	LibGraph2::ARGB GetFillColor() const { return m_colFillColor; }
	LibGraph2::ARGB GetBaseFillColor() const { return m_baseColFillColor; }
	float GetThickness() const { return m_fThickness; }
	LibGraph2::pen_DashStyles GetStyle() const { return m_eStyle; }

	//SETTERS
	void SetP1(const LibGraph2::CPoint& pt);
	void SetColor(LibGraph2::ARGB color) { m_colColor = color; }
	void SetFillColor(LibGraph2::ARGB color) { m_colFillColor = color; }
	void SetBAseFillColor(LibGraph2::ARGB color) { m_baseColFillColor = color; }
	void SetThickness(float thickness) { m_fThickness = thickness; }
	void SetStyle(LibGraph2::pen_DashStyles style) { m_eStyle = style; }
};
