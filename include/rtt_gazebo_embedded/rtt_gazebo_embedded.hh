#ifndef __GZ_EMBEDDED__
#define __GZ_EMBEDDED__

// Gazebo headers
#include <gazebo/gazebo.hh>
#include <gazebo/common/common.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/sensors/sensors.hh>
#include <gazebo/sensors/SensorsIface.hh>
#include <gazebo/sensors/SensorManager.hh>
// RTT headers
#include <rtt/TaskContext.hpp>
#include <rtt/Component.hpp>
#include <rtt/Port.hpp>
#include <rtt/os/Semaphore.hpp>

#include <thread>

class RTTGazeboEmbedded : public RTT::TaskContext
{
public:
    RTTGazeboEmbedded(const std::string& name);
    void addPlugin(const std::string& filename);
    void setWorldFilePath(const std::string& file_path);
    bool configureHook();
//    bool spawnModel(const std::string& instanceName, const std::string& modelName);
    bool spawnModel(const std::string& instanceName,
    		const std::string& modelName, const int timeoutSec);
    bool toggleDynamicsSimulation(const bool activate);

    virtual ~RTTGazeboEmbedded();

protected:
    void WorldUpdateBegin();
    void WorldUpdateEnd();
    void OnPause(const bool _pause);

    bool resetModelPoses();
    bool resetWorld();

    bool startHook();
    void runWorldForever();
    void updateHook();
    void stopHook();

    void cleanupHook();

    void pauseSimulation();
    void unPauseSimulation();

    std::string world_path;
    gazebo::physics::WorldPtr world;
    gazebo::event::ConnectionPtr world_begin;
    gazebo::event::ConnectionPtr world_end;
    gazebo::event::ConnectionPtr pause;

    std::vector<double> gravity_vector;
    std::vector<std::string> argv;
    std::atomic<bool> stop_sensor_th;
    bool use_rtt_sync;
    RTT::os::Semaphore go_sem;

    std::thread run_th;

    std::atomic<bool> is_paused;

    bool is_world_configured;
    int n_sensors;
};

#endif
