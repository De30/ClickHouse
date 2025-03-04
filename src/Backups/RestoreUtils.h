#pragma once

#include <Parsers/ASTBackupQuery.h>
#include <Common/ThreadPool.h>


namespace DB
{

class IBackup;
using BackupPtr = std::shared_ptr<const IBackup>;
class IRestoreTask;
using RestoreTaskPtr = std::unique_ptr<IRestoreTask>;
using RestoreTasks = std::vector<RestoreTaskPtr>;
struct RestoreSettings;
class IRestoreCoordination;
class Context;
using ContextPtr = std::shared_ptr<const Context>;
using ContextMutablePtr = std::shared_ptr<Context>;

/// Prepares restore tasks.
RestoreTasks makeRestoreTasks(ContextMutablePtr context, const BackupPtr & backup, const ASTBackupQuery::Elements & elements, const RestoreSettings & restore_settings, const std::shared_ptr<IRestoreCoordination> & restore_coordination, std::chrono::seconds timeout_for_restoring_metadata);

/// Executes restore tasks.
void executeRestoreTasks(RestoreTasks && tasks, ThreadPool & thread_pool, const RestoreSettings & restore_settings, const std::shared_ptr<IRestoreCoordination> & restore_coordination, std::chrono::seconds timeout_for_restoring_metadata);

}
