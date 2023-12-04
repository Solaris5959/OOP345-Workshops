// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		
		bool isBanned = false;

        for (size_t i = 0; i < allProfiles.size(); ++i) {
            isBanned = false;
            for (size_t j = 0; j < bannedProfiles.size() && !isBanned; ++j) 
                isBanned = (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name &&
                    allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name &&
                    allProfiles[i].m_age == bannedProfiles[j].m_age);

            if (!isBanned) {
                Profile* newProfile = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
                try {

                    newProfile->validateAddress();
                }
                catch (...)
                {
                    delete newProfile;
                    throw;
                }
                result += newProfile;
                delete newProfile;
            }
        }
		return result;
	}
}
