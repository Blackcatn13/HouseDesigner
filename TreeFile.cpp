#include "TreeFile.h"

TreeFile *TreeFile::m_TreeFile = 0;

TreeFile::TreeFile()
{
    m_dir->GetInstance();

}

TreeFile* TreeFile::GetInstance()
{
    if (m_TreeFile == NULL)
        m_TreeFile = new TreeFile();
    return m_TreeFile;
}

