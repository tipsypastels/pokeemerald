#include "global.h"
#include "graphics.h"
#include "event_data.h"
#include "string_util.h"
#include "text.h"
#include "menu.h"
#include "window.h"
#include "sprite.h"
#include "strings.h"
#include "decompress.h"
#include "quest.h"
#include "constants/flags.h"
#include "constants/vars.h"

static const u8 sTestQuestName[] = _("Test Quest");
static const u8 sTestQuestStepName[] = _("Test Step");
static const u8 sTestQuestStepName2[] = _("Test Step 2");

static bool8 IsOnLastQuestStep(u16);
static struct QuestStep GetCurrentQuestStep(u16);
static void AdvanceQuest_UNSAFE(struct Quest);

static const struct Quest sQuestList[] = {
  {
    .name = sTestQuestName,
    .ongoingFlag = FLAG_UNUSED_0x935,
    .completedFlag = FLAG_UNUSED_0x936,
    .progressVar = VAR_UNUSED_0x404E,
    .firstStepIdx = 0,
    .lastStepIdx = 1,
  },
};

static const struct QuestStep sQuestSteps[] = {
  { sTestQuestStepName, 0 },
  { sTestQuestStepName2, 0 },
};

bool8 GiveQuest(u16 questId) {
  bool8 success = GiveQuestSilent(questId);
  if (success) {
    // log
  }
  return success;
}

bool8 GiveQuestSilent(u16 questId) {
  const struct Quest quest = sQuestList[questId];

  if (HasOrCompletedQuest(questId)) {
    return FALSE;
  }

  if (quest.ongoingFlag == 0) {
    return FALSE;
  }

  FlagSet(quest.ongoingFlag);
  return TRUE;
}

bool8 HasQuest(u16 questId) {
  const struct Quest quest = sQuestList[questId];
  
  if (quest.ongoingFlag == 0) {
    return FALSE;
  }

  return FlagGet(quest.ongoingFlag);
}

bool8 DidCompleteQuest(u16 questId) {
  const struct Quest quest = sQuestList[questId];

  if (quest.completedFlag == 0) {
    return FALSE;
  }

  return FlagGet(quest.completedFlag);
}

bool8 HasOrCompletedQuest(u16 questId) {
  return HasQuest(questId) || DidCompleteQuest(questId);
}

void ResetQuest(u16 questId) {
  const struct Quest quest = sQuestList[questId];

  if (quest.ongoingFlag != 0) {
    FlagClear(quest.ongoingFlag);
  }

  if (quest.completedFlag != 0) {
    FlagClear(quest.completedFlag);
  }
}

void AdvanceQuest(u16 questId) {
  const struct Quest quest = sQuestList[questId];

  if (quest.progressVar == 0) {
    return;
  }

  if (IsOnLastQuestStep(questId)) {
    CompleteQuest(questId);
  } else {
    AdvanceQuest_UNSAFE(quest);
  }
}

void CompleteQuest(u16 questId) {
  const struct Quest quest = sQuestList[questId];
  
  if (quest.completedFlag != 0) {
    FlagSet(quest.completedFlag);
  }

  if (quest.ongoingFlag != 0) {
    FlagClear(quest.ongoingFlag);
  }
}

/**
 * Doesn't check that the quest is ready for completion before advancing it. Never call this directly.
 */
static void AdvanceQuest_UNSAFE(struct Quest quest) {
  u16 *ptr = GetVarPointer(quest.progressVar);
  *ptr += 1;
}

u16 GetCurrentQuestStepId(u16 questId) {
  const struct Quest quest = sQuestList[questId];
  
  if (quest.progressVar == 0) {
    return 0;
  }

  return VarGet(quest.progressVar);
}

static struct QuestStep GetCurrentQuestStep(u16 questId) {
  const struct Quest quest = sQuestList[questId];
  return sQuestSteps[quest.firstStepIdx + GetCurrentQuestStepId(questId)];
}

static bool8 IsOnLastQuestStep(u16 questId) {
  const struct Quest quest = sQuestList[questId];
  return GetCurrentQuestStepId(questId) == quest.lastStepIdx;
}

/**
 * No safety check, maybe add one?
 */
void SetQuestStep(u16 questId, u16 stepId) {
  const struct Quest quest = sQuestList[questId];
  
  if (quest.progressVar == 0) {
    return;
  }

  VarSet(quest.progressVar, stepId - quest.firstStepIdx);
}