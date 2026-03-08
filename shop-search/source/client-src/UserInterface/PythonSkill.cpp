# Search

PyObject * skillGetSkillName(PyObject * poSelf, PyObject * poArgs)

# Change

PyObject * skillGetSkillName(PyObject * poSelf, PyObject * poArgs)
{
	int iSkillIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iSkillIndex))
		return Py_BadArgument();

	int iSkillGrade = -1;
	PyTuple_GetInteger(poArgs, 1, &iSkillGrade);

	CPythonSkill::SSkillData * c_pSkillData;
	if (!CPythonSkill::Instance().GetSkillData(iSkillIndex, &c_pSkillData))
		//return Py_BuildException("skill.GetSkillName - Failed to find skill by %d", iSkillIndex);
		return Py_BuildValue("s","NoneSkill");

	if (-1 != iSkillGrade)
		if (iSkillGrade >= 0 && iSkillGrade < CPythonSkill::SKILL_GRADE_COUNT)
		{
			return Py_BuildValue("s", c_pSkillData->GradeData[iSkillGrade].strName.c_str());
		}

	return Py_BuildValue("s", c_pSkillData->strName.c_str());
}